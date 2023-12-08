using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class LevelParser : MonoBehaviour
{
    public TextAsset level;
    public int ReadIndex = 0;
    private int index = 0;

    public void PrintLineAtIndex()
    {
        string levelText = level.text;
        string[] lines = levelText.Split(new char[] {'\n'});
        Debug.Log(lines[ReadIndex]);
    }

    public void CreateObject()
    {
        index = 0;

        string levelText = level.text;
        string[] lines = levelText.Split(new char[] { '\n' });

        bool finishedGameObjects = false;
        string objectName = " ";
        PrimitiveType type = PrimitiveType.Cube;
        Vector3 pos = new Vector3(0, 0, 0);
        Vector3 rot = new Vector3(0, 0, 0);
        Vector3 scale = new Vector3(0, 0, 0);
        bool hasRigidBody = false;
        float mass = 0f;
        bool gravityEnabled = false;
        bool isPhysicsPlane = false;

        while (!finishedGameObjects)
        {
            // Object Name
            objectName = lines[index];
            index++;

            // Object Type
            if (lines[index].Contains('2') || lines[index].Contains('3')) // Cube or Physics Cube
            {
                type = PrimitiveType.Cube;
            }
            else if(lines[index].Contains('4')) // Plane 
            {
                // Will use cube for plane just so it's more consisent in terms of scale
                type = PrimitiveType.Cube;  
            }
            else if(lines[index].Contains('5')) // Physics Plane
            {
                type = PrimitiveType.Cube;
                isPhysicsPlane = true;
            }
            index++;

            // Object Pos
            string[] posText = lines[index].Split(' '); // Split by spaces
            float posX = float.Parse(posText[1]);
            float posY = float.Parse(posText[2]);
            float posZ = float.Parse(posText[3]);
            pos = new Vector3(posX, posY, posZ);
            index++;

            // Object Rot
            string[] rotText = lines[index].Split(' '); // Split by spaces
            float rotX = float.Parse(rotText[1]);
            float rotY = float.Parse(rotText[2]);
            float rotZ = float.Parse(rotText[3]);
            rot = new Vector3(rotX, rotY, rotZ);
            index++;

            // Object Scale
            string[] scaleText = lines[index].Split(' '); // Split by spaces
            float scaleX = float.Parse(scaleText[1]);
            float scaleY = float.Parse(scaleText[2]);
            float scaleZ = float.Parse(scaleText[3]);     
            scale = new Vector3(scaleX, scaleY, scaleZ);
            index++;

            if (lines[index].Contains("Has Rigidbody"))
            {
                hasRigidBody = true;
                index++;
                // Get Mass
                string[] massText = lines[index].Split(' '); // Split by spaces
                mass = float.Parse(massText[0]);
                index++;
                // Get Is Gravity Enabled
                if (lines[index].Contains("GravityEnabled"))
                    gravityEnabled = true;
                else if(lines[index].Contains("GravityDisabled"))
                    gravityEnabled = false;
                index++;

                // Create Object
                GameObject gameObject = GameObject.CreatePrimitive(type);
                gameObject.name = objectName;
                gameObject.transform.position = pos;
                Vector3 degreeRot = rot * Mathf.Rad2Deg;
                gameObject.transform.localEulerAngles = degreeRot;
                gameObject.transform.localScale = scale;

                Rigidbody rb = gameObject.AddComponent<Rigidbody>();   
                rb.mass = mass; 
                rb.useGravity = gravityEnabled;
                if(isPhysicsPlane)
                    rb.isKinematic = true;  

                if (lines[index].Contains("CubeCount:"))
                {
                    finishedGameObjects = true;
                    index = 0;
                }
                else
                {
                    hasRigidBody = false;
                    mass = 0f;
                    gravityEnabled = false;
                    isPhysicsPlane = false;
                }
            }
            else if (lines[index].Contains("CubeCount:"))
            {
                // Create Object
                GameObject gameObject = GameObject.CreatePrimitive(type);
                gameObject.name = objectName;
                gameObject.transform.position = pos;
                Vector3 degreeRot = rot * Mathf.Rad2Deg;
                gameObject.transform.localEulerAngles = degreeRot;
                gameObject.transform.localScale = scale;

                finishedGameObjects = true;
                index = 0;
            }
            else
            {
                // Create Object
                GameObject gameObject = GameObject.CreatePrimitive(type);
                gameObject.name = objectName;
                gameObject.transform.position = pos;
                Vector3 degreeRot = rot * Mathf.Rad2Deg;
                gameObject.transform.localEulerAngles = degreeRot;
                gameObject.transform.localScale = scale;
            }
        }
    }

    public int GetIndex()
    {
        return index;
    }

}

/*
References:
1. Reading Text Files: https://www.youtube.com/watch?v=sXjhwKPoEVA
2. Text Splitting: https://forum.unity.com/threads/solved-reading-textasset-and-splitting-into-lines-leaves-out-words.474231/
 */