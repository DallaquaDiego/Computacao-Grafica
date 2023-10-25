#include <gl/glut.h>

GLfloat aspecto, angulo, rotacao = 0;

void desenhaObjetos(void)
{
    glClear(GL_COLOR_BUFFER_BIT);              //buffer padr�o (limpa a tela toda vez que a fun��o � chamada)

    glPushMatrix();                            //insere a matriz de transforma��o corrente na pilha
        glRotatef(rotacao, 0, 1, 0);           //realiza a rota��o no eixo y
        glColor4f(0, 0, 1, 1.0);               //adiciona cor a nossa forma
        glutSolidSphere(20, 30, 30);           //cria uma forma 3d s�lida

        glTranslatef(0, 0, 10);                //translada no eixo z
        glColor4f(1, 0, 0, 0.2);               //adiciona cor a nossa forma (setando alpha pra 0.2)
        glutSolidSphere(20, 30, 30);           //cria uma forma 3d s�lida
     glPopMatrix();                            //retira a matriz do topo da pilha e torna esta �ltima a matriz de transforma��o corrente

    glutSwapBuffers();
}

void Inicializa(void){
    glClearColor(0,0,0,1);                                 //especifica que a cor de fundo da janela ser� preta
    angulo = 20;                                           //inicializa nossa vari�vel angulo

    //Para exibir objetos transparentes, deve-se utilizar as Fun��es de Blend. Estas fun��es misturam a cor do objeto que est� na tela com cor do objeto que est� sendo desenhado.
    glEnable(GL_BLEND);                                    //ativa as fun��es de BLEND
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     //o primeiro argumernto define o peso da cor do novo ponto e o segundo o peso da cor do ponto que j� est� na tela. Este pesos, em OpenGL, sr�o sempre uma fun��o do n�vel de transpar�ncia do objeto, ou seja, de seu alfa.
}
void projetaPlano(void){
    glMatrixMode(GL_PROJECTION);                    //proje��o dos pontos definidos no plano cartesiano
    glLoadIdentity();                               //carrega a proje��o
    gluPerspective(angulo, aspecto, 0.1, 500);      //fun��o que estabelece os par�metros da Proje��o Perspectiva, atualizando a matriz de proje��o perspectiva.
    glMatrixMode(GL_MODELVIEW);                     //proje��o do tipo modelo
    glLoadIdentity();                               //carrega a identidade de proje��o de modelo
    gluLookAt(0, 300, 300, 0, 0, 0, 0, 1, 0);              //Especifica posi��o do observador e do alvo
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){      //faz o controle do tamanho das viewports (padr�o de par�metros, altura e largura) (800x600 no glutInitWindowSize)
    if ( h == 0 ) h = 1;                             //caso altura seja = 0, setamos ela pra 1, pra corrigir eventuais erros
    glViewport(0, 0, w, h);                          //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    aspecto = (GLfloat)w/(GLfloat)h;                 //largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma propor��o em cada viewport)
    projetaPlano();                                  //chama a fun��o projetaPlano
}

/*fun��o que atriui valores as nossas vari�veis de movimenta��o x e y (dependendo da tecla pressionada) */
void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){                                         //escolhe a tecla pressionada
            case GLUT_KEY_RIGHT: rotacao+=3;               //rotaciona nosso objeto sentido hor�rio
            break;
            case GLUT_KEY_LEFT: rotacao-=3;                //rotaciona nosso objeto sentido anti-hor�rio
            break;
    }
    projetaPlano();                                        //chama a fun��o projetaPlano
    glutPostRedisplay();                                   //redesenha a cena que est� na janela
}

int main(void){
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);       //somente um double buffer | sistema de cores RGB
     glutInitWindowSize(800,600);                       //define o tamanho da janela
     glutInitWindowPosition(300,120);                   //medidas usadas para posicionar a janela no meio da tela - isso depende da resolu��o do monitor
     glutCreateWindow("Exemplo Ilumina��o");            //permite a cria��o de uma janela
     glutDisplayFunc(desenhaObjetos);                   //fun��o de callback - chama a fun��o desenhaObjetos
     glutSpecialFunc(teclasDirecionais);                //chama a fun��o que escuta nossas teclas direcionais
     glutReshapeFunc(AlteraTamanhoJanela);              //fun��o que altera o tamanho da janela, redesenha o tamanho da janela
     Inicializa();                                      //fun��o que inicializa nossas vari�veis
     glutMainLoop();                                    //loop infinito - escuta as informa��es do sistema at� encerrar a aplica��o
     return 0;                                          //retorna zero
}
