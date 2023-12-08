using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Test))]
public class TestEditor : Editor
{
    public override void OnInspectorGUI()
    {
        Test myTest = (Test)target;
        myTest.xp = EditorGUILayout.IntField("XP", myTest.xp);
        EditorGUILayout.LabelField("Slimes Killed", myTest.KilledSlime.ToString());
    }
}
