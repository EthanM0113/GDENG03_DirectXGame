using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

[CustomEditor(typeof(LevelParser))]  
public class LevelParserEditor : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();

        LevelParser myLevelParser = (LevelParser)target;
        EditorGUILayout.LabelField("Index", myLevelParser.GetIndex().ToString());   

        if(GUILayout.Button("Read Line"))
        {
            myLevelParser.PrintLineAtIndex();
        }
        if (GUILayout.Button("Create Object From File"))
        {
            myLevelParser.CreateObject();
        }

    }
}
