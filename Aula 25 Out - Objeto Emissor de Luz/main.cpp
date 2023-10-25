#include <GL/glut.h>
#include <stdio.h>

//Define os parâmetros da luz de
GLfloat luzAmbiente[4] = {0.3, 0.0, 0.0, 1.0};
GLfloat luzDifusa[4]  = {1.0, 0.0, 0.0, 1.0};
GLfloat luzEspecular[4]={1.0,1.0,1.0,1.0};
GLfloat posicaoLuz[4]  = {8.0, 8.0, 15.0,1.0};
GLint especMaterial = 60;

GLfloat aspecto, angulo;

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

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angulo, aspecto, 0.4, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0,0,30, 0,0,0, 0,1,0);

    glPushMatrix();

        glTranslatef(posicaoLuz[0],posicaoLuz[1],posicaoLuz[2]);
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
		glutSolidSphere(0.1,100,100);

    glPopMatrix();

    glPushMatrix();
        glutSolidSphere(8, 100,100);
	glPopMatrix();

   glutSwapBuffers();

}

void AlteraTamanhoJanela(int w, int h){

    glViewport(0, 0, w, h);
    aspecto = (GLfloat)w/(GLfloat)h;

}

void teclasEspeciais(int tecla, int x, int y){

    switch (tecla){
        case GLUT_KEY_LEFT: posicaoLuz[0]-=0.2;               //move a luz pra esqueda -x
            break;

        case GLUT_KEY_RIGHT: posicaoLuz[0]+=0.2;              //move a luz pra direira +x
            break;

        case GLUT_KEY_UP: posicaoLuz[1]+=0.2;                 //move a luz pra cima  +y
            break;

        case GLUT_KEY_DOWN:	posicaoLuz[1]-=0.2;               //move a luz pra baixo -y
            break;

        case GLUT_KEY_PAGE_DOWN: posicaoLuz[2]-=0.2;          //move a luz pra trás -z
        break;

        case GLUT_KEY_PAGE_UP: posicaoLuz[2]+=0.2;            //move a luz pra frente +z
            break;

   }

   glutPostRedisplay();

}

int main(void) {

     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Exemplo Sombreamento");
     glutDisplayFunc(desenhaObjetos);
     glutSpecialFunc(teclasEspeciais);
     glutReshapeFunc(AlteraTamanhoJanela);
     inicializaLuzes();
     glClearColor (0,0,0,1);
     angulo = 60;
     glutPostRedisplay();
     glutMainLoop();

     return 0;

}
