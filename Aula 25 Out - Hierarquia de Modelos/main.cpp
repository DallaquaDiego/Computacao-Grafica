#include <gl/glut.h>
//#include <stdio.h>

GLfloat aspecto, angulo, rotA, rotB;            //aspecto: variável para controlar windowsize; angulo: para projeção/perspectiva; rotação: para o objeto. rotA e RotB: rotação dos elementos 1 e 2
GLint largura, altura;                          //largura e altura da minha janela

int selected = 1;                               // variável de controle para saber se estamos controlando os dois elementos (A ou 1) ou apenas um (B ou 2)

void desenhaObjetos(void)
{
     glClear(GL_COLOR_BUFFER_BIT);              //buffer padrão (limpa a tela toda vez que a função é chamada)
     glColor3f(1,0,0);                          //adiciona cor a nossa forma
     glPushMatrix();                            //insere a matriz de transformação corrente na pilha
        glRotatef(rotA, 0,0,1);                 //rotaciona os dois elementos juntos
        glTranslatef(1,0,0);                    //translada o objeto no eixo x

        glPushMatrix();                        //insere a matriz de transformação corrente na pilha
            glScalef(2, 0.5, 0.5);             //escalona nosso cubo para ele virar um paralelepípedo
            glutSolidCube(1);                  //cria uma forma 3d sólida
        glPopMatrix();                         //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

        glTranslatef(1,0,0);                   //translada o objeto no eixo x
        glRotatef(rotB, 0,0,1);                //rotaciona apenas o elemento B
        glTranslatef(1,0,0);                   //translada o objeto no eixo x

        glPushMatrix();                        //insere a matriz de transformação corrente na pilha
            glScalef(2, 0.5, 0.5);             //escalona nosso cubo para ele virar um paralelepípedo
            glutSolidCube(1);                  //cria uma forma 3d sólida
        glPopMatrix();                         //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

     glPopMatrix();                            //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente
     glutSwapBuffers();                        //Executa uma troca de buffer na camada em uso para a janela atual (para que consiga trabalhar com dois buffers)
}

void inicializa (void)
{
    glClearColor(1,1,1,0);                     //buffer padrão (limpa a tela toda vez que a função é chamada)
    angulo = 1;                                //inicializa com valor 1 nosso ângulo
}

void projetaPlano(void){
    glMatrixMode(GL_PROJECTION);                    //projeção dos pontos definidos no plano cartesiano
    glLoadIdentity();                               //carrega a projeção
    gluPerspective(angulo, aspecto, 0.1, 500);      //função que estabelece os parâmetros da Projeção Perspectiva, atualizando a matriz de projeção perspectiva.
    glMatrixMode(GL_MODELVIEW);                     //projeção do tipo modelo
    glLoadIdentity();                               //carrega a identidade de projeção de modelo
    gluLookAt(0, 300, 300, 0, 0, 0, 0, 1, 0);       //define a transformação de visualização, através dos argumentos é possível indicar a posição da câmera (para onde ela está direcionada).
}

void alteraTamanhoJanela(GLsizei w, GLsizei h){     //faz o controle do tamanho das viewports (padrão de parâmetros, altura e largura) (800x600 no glutInitWindowSize)
    glViewport(0, 0, w, h);                         //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    largura = w;                                    //altura eu mantenho a mesma, pois não vou dividir a janela.
    altura = h;                                     //largura eu mantenho a mesma, pois não vou dividir a janela.
    aspecto = (float)largura / altura;              //largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma proporção em cada viewport)
    projetaPlano();                                 //chama a função projetaPlano
}

void teclas(unsigned char tecla, int x, int y){
    switch(tecla){
        case '1':
            selected = 1;       //caso seja pressionada a tecla '1', altera o valor da variável
        break;
        case '2':
            selected = 2;       //caso seja pressionada a tecla '2', altera o valor da variável
        break;
    }
}

void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT:
            if(selected == 1) rotA = ((int) rotA + 5) % 360;          //permite rotacionar a esquerda em 360º nossos dois objetos
                if(selected == 2) rotB = ((int) rotB + 5) % 360;      //permite rotacionar a esquerda em 360º nosso objeto 2
        break;
        case GLUT_KEY_RIGHT:
            if(selected == 1) rotA = ((int) rotA - 5) % 360;          //permite rotacionar a direita em 360º nossos dois objetos
                if(selected == 2) rotB = ((int) rotB - 5) % 360;      //permite rotacionar a direita em 360º nosso objeto 2
        break;
    }
    glutPostRedisplay();                                              //redesenha a cena que está na janela
}

int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //somente um double buffer | sistema de cores RGB
     glutInitWindowSize(800,600);                   //define o tamanho da janela
     glutInitWindowPosition(300,120);               //medidas usadas para posicionar a janela no meio da tela - isso depende da resolução do monitor
     glutCreateWindow("Exemplo de Menu");           //permite a criação de uma janela
     glutDisplayFunc(desenhaObjetos);               //função de callback - chama a função desenhaObjetos
     glutSpecialFunc(teclasDirecionais);            //chama a função que escuta nossas teclas direcionais
     glutKeyboardFunc(teclas);                      // Chamada da função teclado (cada pressionamento gera uma chamada do teclado)
     glutReshapeFunc(alteraTamanhoJanela);          //função que altera o tamanho da janela, redesenha o tamanho da janela
     inicializa();                                  //função que inicializa nossas variáveis
     glutMainLoop();                                //loop infinito - escuta as informações do sistema até encerrar a aplicação
     return 0;                                      //retorna zero
}
