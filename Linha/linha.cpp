#include <GL/glut.h>
#include <stdlib.h>

// prototipos das funcoes
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

// funcao principal
int main(int argc, char** argv){
  glutInit(&argc, argv);                         // inicializa o glut
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  // especifica uso de cores e buffers
  glutInitWindowSize (256, 256);                 // especifica as dimensoes da janela
  glutInitWindowPosition (100, 100);             // especifica aonde a janela aparece na tela
  glutCreateWindow ("Desenhando uma linha");     // cria a janela
  init();
  glutDisplayFunc(display);               // funcao que sera redesenhada pelo GLUT
  glutKeyboardFunc(keyboard);             // funcoes de teclado
  glutMainLoop();                         // mostra todas as janelas criadas
  return 0;
}

// definicao de cada funcao

void init(void){
  glClearColor(0.0, 0.0, 1.0, 1.0);    // cor de fundo #QUESTAO 2
  glOrtho(0, 256, 0, 256, -1 ,1);      // modo de projecao ortogonal
} 

void display(void)
{
  int i;
  glClear(GL_COLOR_BUFFER_BIT);               // limpa a janela
  glColor3f (1.0, 0.0, 0.0);                  // cor da linha
  glLineWidth(4.0); 
  //glBegin(GL_LINES);
  glBegin(GL_QUADS);  // #QUESTAO 3
  //glVertex2i(40,200);  glVertex2i(400,10);  // coordenadas inicial e final da linha #QUESTAO 1
  glVertex2i(50,200); glVertex2i(200,200);    // CIMA
  glVertex2i(50,50); glVertex2i(200,50);      // BAIXO
  glVertex2i(200,50); glVertex2i(200,200);    //LADO DIREITO
  glVertex2i(50,50); glVertex2i(50,200);      //LADO ESQUERDO
  glEnd();
  glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 69:
  case 101:	
  case 27:                        // tecla Esc (encerra o programa)
	exit(0);
	break;
  }
}

