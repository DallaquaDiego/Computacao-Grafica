#include <gl/glut.h>
//#include <stdio.h>

GLfloat aspecto, angulo, rotA, rotB;            //aspecto: vari�vel para controlar windowsize; angulo: para proje��o/perspectiva; rota��o: para o objeto. rotA e RotB: rota��o dos elementos 1 e 2
GLint largura, altura;                          //largura e altura da minha janela

int selected = 1;                               // vari�vel de controle para saber se estamos controlando os dois elementos (A ou 1) ou apenas um (B ou 2)

void desenhaObjetos(void)
{
     glClear(GL_COLOR_BUFFER_BIT);              //buffer padr�o (limpa a tela toda vez que a fun��o � chamada)
     glColor3f(1,0,0);                          //adiciona cor a nossa forma
     glPushMatrix();                            //insere a matriz de transforma��o corrente na pilha
        glRotatef(rotA, 0,0,1);                 //rotaciona os dois elementos juntos
        glTranslatef(1,0,0);                    //translada o objeto no eixo x

        glPushMatrix();                        //insere a matriz de transforma��o corrente na pilha
            glScalef(2, 0.5, 0.5);             //escalona nosso cubo para ele virar um paralelep�pedo
            glutSolidCube(1);                  //cria uma forma 3d s�lida
        glPopMatrix();                         //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

        glTranslatef(1,0,0);                   //translada o objeto no eixo x
        glRotatef(rotB, 0,0,1);                //rotaciona apenas o elemento B
        glTranslatef(1,0,0);                   //translada o objeto no eixo x

        glPushMatrix();                        //insere a matriz de transforma��o corrente na pilha
            glScalef(2, 0.5, 0.5);             //escalona nosso cubo para ele virar um paralelep�pedo
            glutSolidCube(1);                  //cria uma forma 3d s�lida
        glPopMatrix();                         //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

     glPopMatrix();                            //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente
     glutSwapBuffers();                        //Executa uma troca de buffer na camada em uso para a janela atual (para que consiga trabalhar com dois buffers)
}

void inicializa (void)
{
    glClearColor(1,1,1,0);                     //buffer padr�o (limpa a tela toda vez que a fun��o � chamada)
    angulo = 1;                                //inicializa com valor 1 nosso �ngulo
}

void projetaPlano(void){
    glMatrixMode(GL_PROJECTION);                    //proje��o dos pontos definidos no plano cartesiano
    glLoadIdentity();                               //carrega a proje��o
    gluPerspective(angulo, aspecto, 0.1, 500);      //fun��o que estabelece os par�metros da Proje��o Perspectiva, atualizando a matriz de proje��o perspectiva.
    glMatrixMode(GL_MODELVIEW);                     //proje��o do tipo modelo
    glLoadIdentity();                               //carrega a identidade de proje��o de modelo
    gluLookAt(0, 300, 300, 0, 0, 0, 0, 1, 0);       //define a transforma��o de visualiza��o, atrav�s dos argumentos � poss�vel indicar a posi��o da c�mera (para onde ela est� direcionada).
}

void alteraTamanhoJanela(GLsizei w, GLsizei h){     //faz o controle do tamanho das viewports (padr�o de par�metros, altura e largura) (800x600 no glutInitWindowSize)
    glViewport(0, 0, w, h);                         //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    largura = w;                                    //altura eu mantenho a mesma, pois n�o vou dividir a janela.
    altura = h;                                     //largura eu mantenho a mesma, pois n�o vou dividir a janela.
    aspecto = (float)largura / altura;              //largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma propor��o em cada viewport)
    projetaPlano();                                 //chama a fun��o projetaPlano
}

void teclas(unsigned char tecla, int x, int y){
    switch(tecla){
        case '1':
            selected = 1;       //caso seja pressionada a tecla '1', altera o valor da vari�vel
        break;
        case '2':
            selected = 2;       //caso seja pressionada a tecla '2', altera o valor da vari�vel
        break;
    }
}

void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT:
            if(selected == 1) rotA = ((int) rotA + 5) % 360;          //permite rotacionar a esquerda em 360� nossos dois objetos
                if(selected == 2) rotB = ((int) rotB + 5) % 360;      //permite rotacionar a esquerda em 360� nosso objeto 2
        break;
        case GLUT_KEY_RIGHT:
            if(selected == 1) rotA = ((int) rotA - 5) % 360;          //permite rotacionar a direita em 360� nossos dois objetos
                if(selected == 2) rotB = ((int) rotB - 5) % 360;      //permite rotacionar a direita em 360� nosso objeto 2
        break;
    }
    glutPostRedisplay();                                              //redesenha a cena que est� na janela
}

int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //somente um double buffer | sistema de cores RGB
     glutInitWindowSize(800,600);                   //define o tamanho da janela
     glutInitWindowPosition(300,120);               //medidas usadas para posicionar a janela no meio da tela - isso depende da resolu��o do monitor
     glutCreateWindow("Exemplo de Menu");           //permite a cria��o de uma janela
     glutDisplayFunc(desenhaObjetos);               //fun��o de callback - chama a fun��o desenhaObjetos
     glutSpecialFunc(teclasDirecionais);            //chama a fun��o que escuta nossas teclas direcionais
     glutKeyboardFunc(teclas);                      // Chamada da fun��o teclado (cada pressionamento gera uma chamada do teclado)
     glutReshapeFunc(alteraTamanhoJanela);          //fun��o que altera o tamanho da janela, redesenha o tamanho da janela
     inicializa();                                  //fun��o que inicializa nossas vari�veis
     glutMainLoop();                                //loop infinito - escuta as informa��es do sistema at� encerrar a aplica��o
     return 0;                                      //retorna zero
}
