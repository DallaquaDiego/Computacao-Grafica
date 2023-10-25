#include <gl/glut.h>

GLfloat aspecto, angulo, rotacao = 0;

void desenhaObjetos(void)
{
    glClear(GL_COLOR_BUFFER_BIT);              //buffer padrão (limpa a tela toda vez que a função é chamada)

    glPushMatrix();                            //insere a matriz de transformação corrente na pilha
        glRotatef(rotacao, 0, 1, 0);           //realiza a rotação no eixo y
        glColor4f(0, 0, 1, 1.0);               //adiciona cor a nossa forma
        glutSolidSphere(20, 30, 30);           //cria uma forma 3d sólida

        glTranslatef(0, 0, 10);                //translada no eixo z
        glColor4f(1, 0, 0, 0.2);               //adiciona cor a nossa forma (setando alpha pra 0.2)
        glutSolidSphere(20, 30, 30);           //cria uma forma 3d sólida
     glPopMatrix();                            //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

    glutSwapBuffers();
}

void Inicializa(void){
    glClearColor(0,0,0,1);                                 //especifica que a cor de fundo da janela será preta
    angulo = 20;                                           //inicializa nossa variável angulo

    //Para exibir objetos transparentes, deve-se utilizar as Funções de Blend. Estas funções misturam a cor do objeto que está na tela com cor do objeto que está sendo desenhado.
    glEnable(GL_BLEND);                                    //ativa as funções de BLEND
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     //o primeiro argumernto define o peso da cor do novo ponto e o segundo o peso da cor do ponto que já está na tela. Este pesos, em OpenGL, srão sempre uma função do nível de transparência do objeto, ou seja, de seu alfa.
}
void projetaPlano(void){
    glMatrixMode(GL_PROJECTION);                    //projeção dos pontos definidos no plano cartesiano
    glLoadIdentity();                               //carrega a projeção
    gluPerspective(angulo, aspecto, 0.1, 500);      //função que estabelece os parâmetros da Projeção Perspectiva, atualizando a matriz de projeção perspectiva.
    glMatrixMode(GL_MODELVIEW);                     //projeção do tipo modelo
    glLoadIdentity();                               //carrega a identidade de projeção de modelo
    gluLookAt(0, 300, 300, 0, 0, 0, 0, 1, 0);              //Especifica posição do observador e do alvo
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){      //faz o controle do tamanho das viewports (padrão de parâmetros, altura e largura) (800x600 no glutInitWindowSize)
    if ( h == 0 ) h = 1;                             //caso altura seja = 0, setamos ela pra 1, pra corrigir eventuais erros
    glViewport(0, 0, w, h);                          //liga viewport com o desenho, aqui eu digo qual janela eu vou utilizar
    aspecto = (GLfloat)w/(GLfloat)h;                 //largura dividida pela altura (utilizada para controlar a largura da janela automaticamente, independente de eu alterar a windowsize) (faz com que as janelas tenham a mesma proporção em cada viewport)
    projetaPlano();                                  //chama a função projetaPlano
}

/*função que atriui valores as nossas variáveis de movimentação x e y (dependendo da tecla pressionada) */
void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){                                         //escolhe a tecla pressionada
            case GLUT_KEY_RIGHT: rotacao+=3;               //rotaciona nosso objeto sentido horário
            break;
            case GLUT_KEY_LEFT: rotacao-=3;                //rotaciona nosso objeto sentido anti-horário
            break;
    }
    projetaPlano();                                        //chama a função projetaPlano
    glutPostRedisplay();                                   //redesenha a cena que está na janela
}

int main(void){
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);       //somente um double buffer | sistema de cores RGB
     glutInitWindowSize(800,600);                       //define o tamanho da janela
     glutInitWindowPosition(300,120);                   //medidas usadas para posicionar a janela no meio da tela - isso depende da resolução do monitor
     glutCreateWindow("Exemplo Iluminação");            //permite a criação de uma janela
     glutDisplayFunc(desenhaObjetos);                   //função de callback - chama a função desenhaObjetos
     glutSpecialFunc(teclasDirecionais);                //chama a função que escuta nossas teclas direcionais
     glutReshapeFunc(AlteraTamanhoJanela);              //função que altera o tamanho da janela, redesenha o tamanho da janela
     Inicializa();                                      //função que inicializa nossas variáveis
     glutMainLoop();                                    //loop infinito - escuta as informações do sistema até encerrar a aplicação
     return 0;                                          //retorna zero
}
