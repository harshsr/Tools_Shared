using System.Collections.Generic;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;

public class ObjectReplacer : EditorWindow
{
    [MenuItem("GameObject/Replace Selected", false, 0)]
    public static void ShowWindow()
    {
        var Window = GetWindow<ObjectReplacer>(true, "Replace Selected");
        Window.minSize = Window.maxSize = new Vector2(250f, 250f);
        Window.autoRepaintOnSceneChange = true;
        Window.Show();
    }

    [SerializeField] private Object ReplacementObject;
    private Texture RefreshIcon;

    private void OnEnable()
    {
        RefreshIcon = EditorGUIUtility.IconContent("Refresh").image;
        if (ReplacementObject == null && !string.IsNullOrEmpty(StoredObjectGUID))
        {
            string Path = AssetDatabase.GUIDToAssetPath(StoredObjectGUID);
            ReplacementObject = AssetDatabase.LoadAssetAtPath<Object>(Path);
        }
    }

    private static string StoredObjectGUID
    {
        get => EditorPrefs.GetString(Application.productName + "_LAST_REPLACEMENT", string.Empty);
        set => EditorPrefs.SetString(Application.productName + "_LAST_REPLACEMENT", value);
    }

    private static bool PreserveScale { get; set; } = true;
    private static bool PreserveRotation { get; set; } = true;
    private static bool PreserveName { get; set; } = false;
    private static bool PreserveLayer { get; set; } = false;
    private static bool PreserveTag { get; set; } = false;

    private void OnGUI()
    {
        if (Selection.gameObjects.Length == 0)
        {
            EditorGUILayout.HelpBox("No objects selected.", MessageType.Warning);
            return;
        }

        EditorGUILayout.LabelField("Select Replacement Object", EditorStyles.boldLabel);
        ReplacementObject = EditorGUILayout.ObjectField(ReplacementObject, typeof(GameObject), true);

        if (ReplacementObject != null)
        {
            StoredObjectGUID = AssetDatabase.AssetPathToGUID(AssetDatabase.GetAssetPath(ReplacementObject));
        }

        EditorGUILayout.Space();

        if (ReplacementObject == null)
        {
            EditorGUILayout.HelpBox("Select a valid object to replace with.", MessageType.Warning);
            return;
        }

        EditorGUILayout.LabelField("Preserve Properties", EditorStyles.boldLabel);
        PreserveScale = EditorGUILayout.Toggle("Scale", PreserveScale);
        PreserveRotation = EditorGUILayout.Toggle("Rotation", PreserveRotation);
        PreserveName = EditorGUILayout.Toggle("Name", PreserveName);
        PreserveLayer = EditorGUILayout.Toggle("Layer", PreserveLayer);
        PreserveTag = EditorGUILayout.Toggle("Tag", PreserveTag);

        EditorGUILayout.Space();

        if (GUILayout.Button(new GUIContent($"Replace {Selection.gameObjects.Length} Objects", RefreshIcon), GUILayout.Height(25f)))
        {
            ReplaceObjects();
        }
    }

    private void ReplaceObjects()
    {
        if (ReplacementObject == null || Selection.gameObjects.Length == 0)
        {
            Debug.LogWarning("No valid objects selected for replacement.");
            return;
        }

        bool IsPrefab = PrefabUtility.GetPrefabAssetType(ReplacementObject) != PrefabAssetType.NotAPrefab;
        List<GameObject> NewSelection = new List<GameObject>();

        foreach (GameObject Selected in Selection.gameObjects)
        {
            GameObject NewObject = ReplaceSingleObject(ReplacementObject, Selected, IsPrefab);
            if (NewObject) NewSelection.Add(NewObject);
        }

        if (NewSelection.Count > 0)
        {
            Selection.objects = NewSelection.ToArray();
            EditorSceneManager.MarkSceneDirty(NewSelection[0].scene);
        }
    }

    private static GameObject ReplaceSingleObject(Object Source, GameObject Target, bool SourceIsPrefab)
    {
        if (!Target.scene.IsValid()) return null;

        GameObject NewObj = SourceIsPrefab ? PrefabUtility.InstantiatePrefab(Source) as GameObject : Instantiate(Source) as GameObject;
        if (NewObj == null) return null;

        Undo.RegisterCreatedObjectUndo(NewObj, "Replace Object");
        NewObj.transform.SetParent(Target.transform.parent, true);
        NewObj.transform.SetSiblingIndex(Target.transform.GetSiblingIndex());
        NewObj.transform.position = Target.transform.position;

        if (PreserveName) NewObj.name = Target.name;
        if (PreserveRotation) NewObj.transform.rotation = Target.transform.rotation;
        if (PreserveScale) NewObj.transform.localScale = Target.transform.localScale;
        if (PreserveTag) NewObj.tag = Target.tag;
        if (PreserveLayer) NewObj.layer = Target.layer;

        Undo.DestroyObjectImmediate(Target);
        return NewObj;
    }
}