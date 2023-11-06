#include <gl/glut.h>

GLfloat aspecto, angulo, rotacao;

void objeto3D(){
    glColor3f(1,0.0,0.0);
    glutSolidTeapot(50);
}

void desenhaObjetos(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angulo, aspecto, 0.4, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(rotacao, 1, 1, 1);
        objeto3D();
    glPopMatrix();

    glutSwapBuffers();
}

void inicializaLuzes(){ //associado a um canal rgb alpha (só na aula de transparência)
    GLfloat luzAmbiente[4] = {0.2,0.2,0.2,1.0}; //se tirar, o objeto reflete sem cor
    GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0}; //
    GLfloat luzEspecular[4] = {1.0,1.0,1.0,1.0}; //sem, não dá para ver o objeto
    GLfloat posicaoLuz[4] = {0.0,0.0,0.1,0.0}; //é o padrão

    //Material
    GLfloat especularidade[4] = {1.0,1.0,1.0,1.0};
    GLfloat especMaterial = 60;

    glShadeModel(GL_SMOOTH); //tipo de sombra

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade); //da onde vem a sombra
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_COLOR_MATERIAL); //desabilitado, o objeto fica só com o material natual, sem cor
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST); //profundidade


}


void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    glViewport(0, 0, w, h);
    aspecto = (GLfloat)w/(GLfloat)h;
}


void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
            case GLUT_KEY_RIGHT: rotacao+=3;
            break;
            case GLUT_KEY_LEFT: rotacao-=3;
            break;
    }
    glutPostRedisplay();
}

int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Exemplo Iluminação");
     glutDisplayFunc(desenhaObjetos);
     glutSpecialFunc(teclasDirecionais);
     glutReshapeFunc(AlteraTamanhoJanela);

     glClearColor(0,0,0,1);
     angulo = 45;
     glutMainLoop();
     return 0;
}
