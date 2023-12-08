using UnityEngine;
using UnityEditor;
using UnityEditor.Experimental.AssetImporters;
using System.IO;
using UnityEditor.AssetImporters;

[ScriptedImporter(1, "level")]
public class LevelImporterEditor : ScriptedImporter
{
    // Imports .level files as text files for Unity to read
    public override void OnImportAsset(AssetImportContext ctx)
    {
        TextAsset subAsset = new TextAsset(File.ReadAllText(ctx.assetPath));
        ctx.AddObjectToAsset("text", subAsset);
        ctx.SetMainObject(subAsset);
    }
}


/*
Reference:
https://forum.unity.com/threads/loading-a-file-with-a-custom-extension-as-a-textasset.625078/
 */