#include <gl/glut.h>


/*

    COMANDOS:
        - Pressione a tecla 'w' para selecionar Marte e controlar sua rotação;
        - Pressione a tecla 's' para selecionar as luas Fobos e Deimos e controlar suas rotações.
        - Pressione a teclas 'a' e 'd' para controlar o sentido das rotações;
        - Para controlar a iluminação utilize as teclas direcionais:
            - Tecla da seta para a esquerda: Move a posição da luz para a esquerda;
            - Tecla da seta para a direita: Move a posição da luz para a direita;
            - Tecla da seta para cima: Move a posição da luz para cima;
            - Tecla da seta para baixo: Move a posição da luz para baixo;
            - Tecla "Page Down" (Page Down key): Move a posição da luz para trás;
            - Tecla "Page Up" (Page Up key): Move a posição da luz para frente.

*/

GLfloat aspecto, angulo;
GLfloat sentido = 0, rotaDeimos, rotaFobos, rotaMarte;

GLfloat fobosX = -45, fobosY = 30, fobosZ = 70;
GLfloat deimosX = 45, deimosY = -30, deimosZ = 50;

GLfloat luzAmbiente[4] = {0.3, 0.0, 0.0, 1.0};
GLfloat luzDifusa[4]  = {1.0, 0.27, 0.0, 0.0};
GLfloat luzEspecular[4]= {1.0,1.0,1.0,1.0};
GLfloat posicaoLuz[4]  = {0.0, 50.0, 100.0,1.0};
GLint especMaterial = 0;

int selected = 0;


// Função para desenhar Marte
void Marte () {

    // Configura a especificidade do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat especMaterial = 60;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Define a cor de Marte e desenha a esfera
    glColor3f(1, 0.27, 0);
    glutSolidSphere(60, 100, 40);

}


// Função para desenhar Fobos
void Fobos () {

    // Configura a especificidade do material
    GLfloat especularidade[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat especMaterial = 0;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Define a cor de Fobos e desenha a esfera
    glColor3f(0.83, 0.83, 0.83);
    glTranslatef(fobosX, fobosY, fobosZ);
    glutSolidSphere(10, 11, 40);

}


// Função para desenhar Deimos
void Deimos () {

    // Configura a especificidade do material
    GLfloat especularidade[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat especMaterial = 0;

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

     // Define a cor de Deimos e desenha a esfera
    glColor3f(0.98, 0.92, 0.84);
    glTranslatef(deimosX, deimosY, deimosZ);
    glutSolidSphere(5, 11, 40);

}


// Função para controlar a rotação das luas e Marte
void movimentaLuas ( int valor ) {

    if ( selected == 1 && sentido == 1 ) {

        rotaMarte -= 0.2;
        rotaDeimos ++;
        rotaFobos --;

    } else if ( selected == 1 && sentido == 0 ) {

        rotaMarte += 0.2;
        rotaDeimos --;
        rotaFobos ++;

    } else {

        if ( sentido == 1 ) {

            rotaDeimos ++;
            rotaFobos --;

        }

        if ( sentido == 0 ) {

            rotaDeimos --;
            rotaFobos ++;

        }

    }

    glutPostRedisplay();

    glutTimerFunc( 10, movimentaLuas, 0 );

}


// Função para lidar com teclas pressionadas pelo usuário
void teclasDirecionais(unsigned char tecla, GLint x, GLint y){

    switch ( tecla ) {

        case 'a' :

            sentido = 1;

        break;

        case 'd' :

            sentido = 0;

        break;

        case 'w':

            selected = 1;

        break;

        case 's':

            selected = 0;

        break;

    }

    glutPostRedisplay();

}


// Função para lidar com teclas especiais, como as teclas de seta
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


// Função para inicializar as configurações de iluminação
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


// Função para ajustar o tamanho da janela
void AlteraTamanhoJanela (GLsizei w, GLsizei h) {

    glViewport ( 0, 0, w, h );
    aspecto = ( float ) w / h;

}


// Função principal
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

        glRotatef( rotaMarte, 1, 1, 1 );
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


// Função principal do programa
int main(void) {
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Projeto OpenGL 3D");

     glutDisplayFunc ( desenhaObjetos );

     glutTimerFunc( 10, movimentaLuas, 0 );

     glutKeyboardFunc ( teclasDirecionais );
     glutSpecialFunc(teclasEspeciais);
     glutReshapeFunc ( AlteraTamanhoJanela );

     inicializaLuzes();

     glClearColor(1,1,1,0);
     angulo = 50;

     glutMainLoop();
     return 0;

}
