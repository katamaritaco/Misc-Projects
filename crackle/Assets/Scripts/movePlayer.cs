using UnityEngine;
using System.Collections;

public class movePlayer : MonoBehaviour {

    Vector3 velocity;

    public float movementSpeed = 8.0f;
    public float jumpSpeed = 10.0f;
    public float mouseSensitivity = 5.0f;
    public float gravity = 10.0f;
    
	// Use this for initialization
	void Start () {
        velocity = new Vector3(0, 0, 0);
	}

    void OnGUI()
    {
        GUI.Label(new Rect(20.0f, 200.0f, 200.0f, 20.0f), gameObject.transform.position.ToString("F3"));
        GUI.Label(new Rect(20.0f, 240.0f, 200.0f, 20.0f), transform.position.ToString("F3"));
    }

	// Update is called once per frame
	void Update () {
        CharacterController charController = gameObject.GetComponent<CharacterController>();
        //velocity = new Vector3(Input.GetAxis("Horizontal") * movementSpeed, 0, Input.GetAxis("Vertical") * movementSpeed);

        //gameObject.transform.Rotate(0, Input.GetAxis("Mouse X"), 0);
        //Camera.main.transform.Rotate(-Input.GetAxis("Mouse Y"), 0, 0);

        velocity.x = Input.GetAxis("Horizontal") * movementSpeed;
        velocity.z = Input.GetAxis("Vertical") * movementSpeed;

        if (charController.isGrounded)
        {
            if (Input.GetButton("Jump"))
            {
                velocity.y = jumpSpeed;
            }
        }
        else {
            velocity.y -= gravity * Time.deltaTime;
        }

        velocity = transform.rotation * velocity;

        gameObject.transform.Rotate(0, Input.GetAxis("Mouse X"), 0);
        Camera.main.transform.Rotate(-Input.GetAxis("Mouse Y"), 0, 0);



        charController.Move(velocity * Time.deltaTime);

	}
}
