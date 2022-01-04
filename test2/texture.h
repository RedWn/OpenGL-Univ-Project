
/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// Counter to keep track of the last loaded texture
extern int num_texture;



/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

extern int LoadTexture(char *filename,int alpha=255);
