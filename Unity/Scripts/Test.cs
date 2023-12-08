using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    public int xp;

    public int KilledSlime
    {
        get { return xp / 10; }
    }
}
