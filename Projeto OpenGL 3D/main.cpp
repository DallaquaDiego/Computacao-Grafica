#include <gl/glut.h>

GLfloat aspecto, angulo;
GLfloat rotaDeimos, rotaFobos;

GLfloat fobosX = -45, fobosY = 30, fobosZ = 70;
GLfloat deimosX = 45, deimosY = -30, deimosZ = 50;

GLfloat luzAmbiente[4] = {0.3, 0.0, 0.0, 1.0};
GLfloat luzDifusa[4]  = {1.0, 0.0, 0.0, 1.0};
GLfloat luzEspecular[4]={1.0,1.0,1.0,1.0};
GLfloat posicaoLuz[4]  = {8.0, 8.0, 15.0,1.0};
GLint especMaterial = 60;

void Marte () {

    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat especMaterial = 60;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Cor de Marte
    glColor3f(1, 0.27, 0);
    glutSolidSphere(60, 100, 40);

}

void Fobos () {

    GLfloat especularidade[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat especMaterial = 0;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Cor de Fobos
    glColor3f(0.83, 0.83, 0.83);
    glTranslatef(fobosX, fobosY, fobosZ);
    glutSolidSphere(10, 11, 40);

}

void Deimos () {

    GLfloat especularidade[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat especMaterial = 0;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Cor de Deimos
    glColor3f(0.98, 0.92, 0.84);
    glTranslatef(deimosX, deimosY, deimosZ);
    glutSolidSphere(5, 11, 40);

}


void AlteraTamanhoJanela (GLsizei w, GLsizei h) {

    glViewport ( 0, 0, w, h );
    aspecto = ( float ) w / h;

}


void teclasDirecionais(unsigned char tecla, GLint x, GLint y){

    switch ( tecla ) {

        case 'a' :

            rotaDeimos += 3;
            rotaFobos -= 3;

        break;

        case 'd' :

            rotaDeimos -= 3;
            rotaFobos += 3;

        break;

    }

    glutPostRedisplay();

}

void teclasEspeciais(int tecla, int x, int y){

    switch (tecla){

        case GLUT_KEY_LEFT:

            posicaoLuz[0]--;               //move a luz pra esqueda

        break;

        case GLUT_KEY_RIGHT:

            posicaoLuz[0]++;              //move a luz pra direira

        break;

        case GLUT_KEY_UP:

            posicaoLuz[1]++;                 //move a luz pra cima

        break;

        case GLUT_KEY_DOWN:

            posicaoLuz[1]--;               //move a luz pra baixo

        break;

        case GLUT_KEY_PAGE_DOWN:

            posicaoLuz[2]--;          //move a luz pra trás

        break;

        case GLUT_KEY_PAGE_UP:

            posicaoLuz[2]++;            //move a luz pra frente

        break;

   }

   glutPostRedisplay();

}


void inicializaLuzes(){

    glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, luzDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


}

void desenhaObjetos(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective( angulo, aspecto, 0.4, 500 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 300, 300, 0, 0, 0, 0, 1, 0 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

        glTranslatef(posicaoLuz[0],posicaoLuz[1],posicaoLuz[2]);
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
		glutSolidSphere(0.1,100,100);

    glPopMatrix();

     glPushMatrix();


        Marte();

        glPushMatrix();

            glRotatef( rotaFobos, 1, 1, 1 );
            Fobos();

        glPopMatrix();

        glPushMatrix();

            glRotatef( rotaDeimos, 1, 1, 1 );
            Deimos();

        glPopMatrix();

     glPopMatrix();

     glutSwapBuffers();

}


int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Projeto OpenGL 3D");

     glutDisplayFunc ( desenhaObjetos );
     glutKeyboardFunc ( teclasDirecionais );
     glutSpecialFunc(teclasEspeciais);
     glutReshapeFunc ( AlteraTamanhoJanela );

     inicializaLuzes();

     glClearColor(1,1,1,0);
     angulo = 50;

     glutMainLoop();
     return 0;
}
