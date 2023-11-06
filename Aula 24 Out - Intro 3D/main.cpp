#include <gl/glut.h>

GLfloat aspecto, angulo, rotacao;

objetos3D(){

    glColor3f( 0, 1, 1 );
    glutSolidSphere( 40 );

    glColor3f( 0, 0, 0 );
    glutWireTeapot( 40 );

}

void desenhaObjetos(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( angulo, aspecto, 0.1, 500 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt( 0, 300, 300, 0, 0, 0, 0, 1, 0 );

     glPushMatrix();

        glRotatef( rotacao, 1, 1, 1 );
        objetos3D();

     glPopMatrix();

     glutSwapBuffers();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){

    glViewport( 0, 0, w, h );
    aspecto = ( float ) w / h;

}

void teclasDirecionais(unsigned char tecla, GLint x, GLint y){

    switch ( tecla ) {

        case 'a' : rotacao += 3;
            break;

        case 'd' : rotacao -= 3;
            break;

    }

    glutPostRedisplay();

}

int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Exemplo Primitivas 3D");
     glutDisplayFunc(desenhaObjetos);
     glutKeyboardFunc(teclasDirecionais);
     glutReshapeFunc(AlteraTamanhoJanela);
     glClearColor(1,1,1,0);
     angulo = 20;
     glutMainLoop();
     return 0;
}
