using System.Collections.Generic;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;

public class ObjectReplacer : EditorWindow
{
    [MenuItem("GameObject/Replace Selected", false, 0)]
    public static void ShowWindow()
    {
        var window = GetWindow<ObjectReplacer>(true, "Replace Selected");
        window.minSize = window.maxSize = new Vector2(250f, 250f);
        window.autoRepaintOnSceneChange = true;
        window.Show();
    }

    [SerializeField] private Object replacementObject;
    private Texture refreshIcon;

    private void OnEnable()
    {
        refreshIcon = EditorGUIUtility.IconContent("Refresh").image;
        if (replacementObject == null && !string.IsNullOrEmpty(StoredObjectGUID))
        {
            string path = AssetDatabase.GUIDToAssetPath(StoredObjectGUID);
            replacementObject = AssetDatabase.LoadAssetAtPath<Object>(path);
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
        replacementObject = EditorGUILayout.ObjectField(replacementObject, typeof(GameObject), true);

        if (replacementObject != null)
        {
            StoredObjectGUID = AssetDatabase.AssetPathToGUID(AssetDatabase.GetAssetPath(replacementObject));
        }

        EditorGUILayout.Space();

        if (replacementObject == null)
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

        if (GUILayout.Button(new GUIContent($"Replace {Selection.gameObjects.Length} Objects", refreshIcon), GUILayout.Height(25f)))
        {
            ReplaceObjects();
        }
    }

    private void ReplaceObjects()
    {
        if (replacementObject == null || Selection.gameObjects.Length == 0)
        {
            Debug.LogWarning("No valid objects selected for replacement.");
            return;
        }

        bool isPrefab = PrefabUtility.GetPrefabAssetType(replacementObject) != PrefabAssetType.NotAPrefab;
        List<GameObject> newSelection = new List<GameObject>();

        foreach (GameObject selected in Selection.gameObjects)
        {
            GameObject newObject = ReplaceSingleObject(replacementObject, selected, isPrefab);
            if (newObject) newSelection.Add(newObject);
        }

        if (newSelection.Count > 0)
        {
            Selection.objects = newSelection.ToArray();
            EditorSceneManager.MarkSceneDirty(newSelection[0].scene);
        }
    }

    private static GameObject ReplaceSingleObject(Object source, GameObject target, bool sourceIsPrefab)
    {
        if (!target.scene.IsValid()) return null;

        GameObject newObj = sourceIsPrefab ? PrefabUtility.InstantiatePrefab(source) as GameObject : Instantiate(source) as GameObject;
        if (newObj == null) return null;

        Undo.RegisterCreatedObjectUndo(newObj, "Replace Object");
        newObj.transform.SetParent(target.transform.parent, true);
        newObj.transform.SetSiblingIndex(target.transform.GetSiblingIndex());
        newObj.transform.position = target.transform.position;

        if (PreserveName) newObj.name = target.name;
        if (PreserveRotation) newObj.transform.rotation = target.transform.rotation;
        if (PreserveScale) newObj.transform.localScale = target.transform.localScale;
        if (PreserveTag) newObj.tag = target.tag;
        if (PreserveLayer) newObj.layer = target.layer;

        Undo.DestroyObjectImmediate(target);
        return newObj;
    }
}