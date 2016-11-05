#include "gl.h"

#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

void gl4es_glTexImage2D(GLenum target, GLint level, GLint internalFormat,
                  GLsizei width, GLsizei height, GLint border,
                  GLenum format, GLenum type, const GLvoid *data);

void gl4es_glTexImage1D(GLenum target, GLint level, GLint internalFormat,
                  GLsizei width, GLint border,
                  GLenum format, GLenum type, const GLvoid *data);

void gl4es_glTexImage3D(GLenum target, GLint level, GLint internalFormat,
                  GLsizei width, GLsizei height, GLsizei depth,
                  GLint border, GLenum format, GLenum type, const GLvoid *data);

void gl4es_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                     GLsizei width, GLsizei height, GLenum format, GLenum type,
                     const GLvoid *data);
                     
void gl4es_glTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                     GLsizei width, GLenum format, GLenum type,
                     const GLvoid *data);
                     
void gl4es_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, 
                     GLsizei width, GLsizei height, GLsizei depth, GLenum format,
                     GLenum type, const GLvoid *data);

void gl4es_glBindTexture(GLenum target, GLuint texture);
void gl4es_glGenTextures(GLsizei n, GLuint * textures);
void gl4es_glDeleteTextures(GLsizei n, const GLuint * textures);
void gl4es_glTexParameteri(GLenum target, GLenum pname, GLint param);
void gl4es_glTexParameterf(GLenum target, GLenum pname, GLfloat param);
GLboolean gl4es_glAreTexturesResident(GLsizei n, const GLuint *textures, GLboolean *residences);
void gl4es_glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params);
void gl4es_glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * img);
void gl4es_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * data);

void gl4es_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat,
							GLsizei width, GLsizei height, GLint border,
							GLsizei imageSize, const GLvoid *data);
void gl4es_glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat,
							GLsizei width, GLint border,
							GLsizei imageSize, const GLvoid *data);
void gl4es_glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat,
							GLsizei width, GLsizei height, GLsizei depth, GLint border,
							GLsizei imageSize, const GLvoid *data);
							
void gl4es_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
							   GLsizei width, GLsizei height, GLenum format, 
							   GLsizei imageSize, const GLvoid *data);
void gl4es_glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset,
							   GLsizei width, GLenum format, 
							   GLsizei imageSize, const GLvoid *data);
void gl4es_glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
							   GLsizei width, GLsizei height, GLsizei depth, GLenum format, 
							   GLsizei imageSize, const GLvoid *data);
                               
void gl4es_glGetCompressedTexImage(GLenum target, GLint lod, GLvoid *img);

                               
void gl4es_glCopyTexImage1D(GLenum target,  GLint level,  GLenum internalformat,  GLint x,  GLint y,  
								GLsizei width,  GLint border);

void gl4es_glCopyTexImage2D(GLenum target,  GLint level,  GLenum internalformat,  GLint x,  GLint y,  
								GLsizei width,  GLsizei height,  GLint border);

void gl4es_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                GLint x, GLint y, GLsizei width, GLsizei height);
                                
void gl4es_glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y,
                                GLsizei width);

void gl4es_glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
                                GLint x, GLint y, GLsizei width, GLsizei height);

void gl4es_glTexEnvf(GLenum target, GLenum pname, GLfloat param);
void gl4es_glTexEnvi(GLenum target, GLenum pname, GLint param);
void gl4es_glTexEnvfv(GLenum target, GLenum pname, const GLfloat *param);
void gl4es_glTexEnviv(GLenum target, GLenum pname, const GLint *param);
void gl4es_glGetTexEnvfv(GLenum target, GLenum pname, GLfloat * params);
void gl4es_glGetTexEnviv(GLenum target, GLenum pname, GLint * params);

                               
void tex_coord_rect_arb(GLfloat *tex, GLsizei len,
                        GLsizei width, GLsizei height);
void tex_coord_npot(GLfloat *tex, GLsizei len,
                    GLsizei width, GLsizei height,
                    GLsizei nwidth, GLsizei nheight);
int npot(int n);

typedef struct {
    GLuint texture;
    GLuint glname;
    GLenum target;
    GLsizei width;
    GLsizei height;
    GLsizei nwidth;
    GLsizei nheight;
    GLenum  format;
    GLenum  type;
    GLenum  orig_internal;
    GLenum  internalformat;
    int shrink;
    GLboolean mipmap_auto;
    GLboolean mipmap_need;
	GLenum min_filter;
	GLenum mag_filter;
    GLenum wrap_s;
    GLenum wrap_t;
    GLboolean uploaded;
    GLboolean alpha;
    GLboolean compressed;
	GLboolean streamed;
	int	streamingID;
    GLvoid *data;	// in case we want to keep a copy of it (it that case, always RGBA/GL_UNSIGNED_BYTE
} gltexture_t;

KHASH_MAP_INIT_INT(tex, gltexture_t *)

static inline GLenum map_tex_target(GLenum target) {
    switch (target) {
        case GL_TEXTURE_1D:
        case GL_TEXTURE_3D:
        case GL_TEXTURE_RECTANGLE_ARB:
            target = GL_TEXTURE_2D;
            break;
        case GL_PROXY_TEXTURE_1D:
        case GL_PROXY_TEXTURE_3D:
            target = GL_PROXY_TEXTURE_2D;
            break;
    }
    return target;
}
gltexture_t* gl4es_getTexture(GLenum target, GLuint texture);

void gl4es_glActiveTexture( GLenum texture );
void gl4es_glClientActiveTexture( GLenum texture );
void gl4es_glMultiTexCoord2f( GLenum target, GLfloat s, GLfloat t );
GLboolean gl4es_glIsTexture( GLuint texture );

void tex_setup_texcoord(GLuint len);

#endif
