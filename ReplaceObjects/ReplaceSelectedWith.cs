
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;
using UnityEngine.Serialization;

public class ReplaceSelectedWith : EditorWindow
{
    [MenuItem("GameObject/Replace Selected With", false, 0)]
    public static void OpenWindow()
    {
        //Show existing window instance. If one doesn't exist, make one.
        ReplaceSelectedWith Window = (ReplaceSelectedWith)EditorWindow.GetWindow(typeof(ReplaceSelectedWith), true);

        //Options
        Window.autoRepaintOnSceneChange = true;
        Window.maxSize = new Vector2(230f, 230f);
        Window.minSize = Window.maxSize;
        Window.titleContent.image = EditorGUIUtility.IconContent("GameObject Icon").image;
        Window.titleContent.text = "Replace Selected With";
        
        Window.Show();
    }

    [FormerlySerializedAs("sourceObject")] [SerializeField]
    private Object SourceObject;
    private static Object SourcePrefab;

    private Texture RefreshIcon;
    private void OnEnable()
    {
        RefreshIcon = EditorGUIUtility.IconContent("Refresh").image;
        
        if (SourceObject != null) return;

        if (LastTargetGUID != string.Empty)
        {
            string Path = AssetDatabase.GUIDToAssetPath(LastTargetGUID);
            SourceObject = (Object)AssetDatabase.LoadAssetAtPath(Path, typeof(Object));
        }
    }

    private static string LastTargetGUID
    {
        get => EditorPrefs.GetString(PlayerSettings.productName + "_REPLACE_LASTGUID", string.Empty);
        set => EditorPrefs.SetString(PlayerSettings.productName + "_REPLACE_LASTGUID", value);
    }

    private static bool KeepScale
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepScale", true);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepScale", value);
    }
    private static bool KeepRotation
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepRotation", true);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepRotation", value);
    }
    private static bool KeepName
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepName", false);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepName", value);
    }
    private static bool KeepPrefabOverrides
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepPrefabOverrides", false);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepPrefabOverrides", value);
    }
    private static bool KeepLayer
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepLayer", false);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepLayer", value);
    }
    private static bool KeepTag
    {
        get => EditorPrefs.GetBool(PlayerSettings.productName + "_REPLACE_KeepTag", false);
        set => EditorPrefs.SetBool(PlayerSettings.productName + "_REPLACE_KeepTag", value);
    }

    private void OnGUI()
    {
        if (Selection.gameObjects.Length == 0)
        {
            EditorGUILayout.HelpBox("Nothing selected", MessageType.Info);
            return;
        }
        
        EditorGUILayout.LabelField("Replacement Object/Prefab", EditorStyles.boldLabel);
        EditorGUI.BeginChangeCheck();
        SourceObject = (Object)EditorGUILayout.ObjectField(SourceObject, typeof(GameObject), true);
        if (EditorGUI.EndChangeCheck())
        {
            LastTargetGUID = SourceObject ? AssetDatabase.AssetPathToGUID(AssetDatabase.GetAssetPath(SourceObject.GetInstanceID())) : string.Empty;
        }
        EditorGUILayout.Space();

        using (new EditorGUI.DisabledGroupScope(SourceObject == null))
        {
            EditorGUILayout.LabelField("Keep Properties", EditorStyles.boldLabel);
            KeepScale = EditorGUILayout.Toggle(new GUIContent("Scale", "Enable to keep the current object's scale"), KeepScale);
            KeepRotation = EditorGUILayout.Toggle(new GUIContent("Rotation", "Enable to keep the current object's rotation"), KeepRotation);
            KeepName = EditorGUILayout.Toggle(new GUIContent("Name", "Enable to keep the current object's name"), KeepName);
            KeepLayer = EditorGUILayout.Toggle(new GUIContent("Layer", "Enable to keep the current object's layer"), KeepLayer);
            KeepTag = EditorGUILayout.Toggle(new GUIContent("Tag", "Enable to keep the current object's tag"), KeepTag);
            KeepPrefabOverrides = EditorGUILayout.Toggle(new GUIContent("Prefab overrides", "If the selected- and replacement objects are a prefab, overrides are copied over to the replaced object"), KeepPrefabOverrides);

            EditorGUILayout.Space();

            if (GUILayout.Button(new GUIContent(" Replace " + Selection.gameObjects.Length + " GameObject" + (Selection.gameObjects.Length > 1 ? "s" : ""), RefreshIcon), GUILayout.Height(25f)))
            {
                ReplaceCurrentSelection();
            }
        }
    }

    private void OnSelectionChange()
    {
        this.Repaint();
    }

    private void ReplaceCurrentSelection()
    {
        if (Selection.gameObjects.Length == 0 || SourceObject == null) return;

        //PrefabUtility.GetCorrespondingObjectFromSource still returns the base prefab. However, this does work.
        SourcePrefab = PrefabUtility.GetPrefabAssetType(SourceObject) == PrefabAssetType.Variant ? SourceObject : PrefabUtility.GetCorrespondingObjectFromOriginalSource(SourceObject);

        //Model prefabs don't count
        var isPrefab = SourcePrefab;
        
        foreach (GameObject selected in Selection.gameObjects)
        {
            Replace(SourceObject, selected, isPrefab);
        }
    }
    
    private static void Replace(Object Source, GameObject Target, bool SourceIsPrefab)
    {
        //Skip anything selected in the project window!
        if (Target.scene.IsValid() == false) return;
        
        GameObject NewObj = null;

        if (PrefabUtility.IsPartOfPrefabInstance(Target) && !PrefabUtility.IsOutermostPrefabInstanceRoot(Target))
        {
            Debug.LogError("Cannot replace an object that's part of a prefab instance. It must be unpacked first.", Target);
            return;
        }

        if (SourceIsPrefab)
        {
            NewObj = PrefabUtility.InstantiatePrefab(SourcePrefab, Target.scene) as GameObject;
            Undo.RegisterCreatedObjectUndo(NewObj, "replaced with prefabs");
            
            //Apply any overrides (added/removed components, parameters, etc)
            if (KeepPrefabOverrides)
            {
                if (PrefabUtility.HasPrefabInstanceAnyOverrides(Target, false))
                {
                    CopyPrefabOverrides(Target, NewObj);
                }
            }
        }
        else
        {
            NewObj = GameObject.Instantiate(Source) as GameObject;
            Undo.RegisterCreatedObjectUndo(NewObj, "replaced object");
            if (NewObj != null) NewObj.name = NewObj.name.Replace("(Clone)", string.Empty);
        }

        if (NewObj != null)
        {
            NewObj.transform.parent = Target.transform.parent;
            NewObj.transform.SetSiblingIndex(Target.transform.GetSiblingIndex());
            NewObj.transform.position = Target.transform.position;

            if (KeepName) NewObj.name = Target.name;
            if (KeepRotation) NewObj.transform.rotation = Target.transform.rotation;
            if (KeepScale) NewObj.transform.localScale = Target.transform.localScale;
            if (KeepTag) NewObj.tag = Target.tag;
            if (KeepLayer) NewObj.layer = Target.layer;

            if (Selection.gameObjects.Length == 1) Selection.activeGameObject = NewObj;
        }

        EditorSceneManager.MarkSceneDirty(Target.scene);
        
        Undo.DestroyObjectImmediate(Target);
    }

    private static void CopyPrefabOverrides(GameObject source, GameObject target)
    {
        //Model prefab don't have real overrides, copy any components instead
        if (PrefabUtility.GetPrefabAssetType(target) == PrefabAssetType.Model)
        {
            Debug.Log(target.name + " is a model prefab");
            CopyComponents(target, source);
            return;
        }
        
        //Get all overrides
        PropertyModification[] overrides = PrefabUtility.GetPropertyModifications(source);
        List<AddedComponent> added = PrefabUtility.GetAddedComponents(source);
        List<RemovedComponent> removed = PrefabUtility.GetRemovedComponents(source);

        //Remove any components removed as an overrides
        for (int i = 0; i < removed.Count; i++)
        {
            Component comp = target.GetComponent(removed[i].assetComponent.GetType());
            DestroyImmediate(comp);
        }

        //Add any components added as overrides and copy the values over
        for (int i = 0; i < added.Count; i++)
        {
            Component copy = target.GetComponent(added[i].instanceComponent.GetType());
            if(!copy) copy = target.AddComponent(added[i].instanceComponent.GetType());
            EditorUtility.CopySerialized(added[i].instanceComponent, copy);
        }

        //PrefabUtility.ApplyPrefabInstance(target, InteractionMode.AutomatedAction);

        //Apply any modified parameters
        PrefabUtility.SetPropertyModifications(target, overrides);
    }

    private static void CopyComponents(GameObject source, GameObject destination)
    {
        Component[] sourceComponents = destination.GetComponents(typeof(Component));

        for (int i = 0; i < sourceComponents.Length; i++)
        {
            //Don't copy Transform or GameObject values
            if(sourceComponents[i].GetType() == typeof(Transform) || sourceComponents[i].GetType() == typeof(GameObject)) continue;
            
            Component newComp = source.GetComponent(sourceComponents[i].GetType());

            if (!newComp)
            {
                newComp = source.AddComponent(sourceComponents[i].GetType());
            }

            //Copy over values, on prefabs these will automatically becomes overrides
            if (newComp)
            {
                UnityEditorInternal.ComponentUtility.CopyComponent(sourceComponents[i]);
                UnityEditorInternal.ComponentUtility.PasteComponentValues(newComp);
            }
        }
    }
}