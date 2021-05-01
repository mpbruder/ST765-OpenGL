#include<stdlib.h>
#include<GL/glut.h>

/**
 *  Medidas dadas em Metros
 */
#define CHAO_ALTURA 0.1
#define PISTA_TRANSLACAO_Y 0.0
#define PISTA_TRANSLACAO_Z 0.0 
#define PISTA_ESCALONAMENTO_X 45.0
#define PISTA_ESCALONAMENTO_Y 0.2
#define GALPAO_ESCALONAMENTO_X 150.0
#define GALPAO_ESCALONAMENTO_Y 50.5
#define GALPAO_ESCALONAMENTO_Z 130.0
#define GALPAO_TRANSLACAO_X -500
#define GALPAO_ESPACAMENTO 20
#define PORTOES_ESCALONAMENTO_X 200.0
#define PORTOES_ESCALONAMENTO_Y 70.0
#define PORTOES_ESCALONAMENTO_Z 1000.0
#define PORTOES_TRANSLACAO_X 600.0
#define PORTAO_ESCALONAMENTO_X 100
#define PORTAO_ESCALONAMENTO_Y 20
#define PORTAO_ESCALONAMENTO_Z 20
#define PORTAO_TRANSLACAO_X PORTOES_TRANSLACAO_X - (PORTOES_ESCALONAMENTO_X/2) - (PORTAO_ESCALONAMENTO_X/2)
#define TORRE_CONTROLE_BASE_RAIO 30
#define TORRE_CONTROLE_BASE_ALTURA 250
#define TORRE_CONTROLE_BASE_SLICES 10
#define TORRE_CONTROLE_BASE_STACKS 10
#define TORRE_CONTROLE_BASE_TRANSLACAO_X GALPAO_TRANSLACAO_X
#define TORRE_CONTROLE_BASE_TRANSLACAO_Z 0.0
#define TORRE_CONTROLE_CABINE_RAIO 60
#define TORRE_CONTROLE_CABINE_ALTURA 60
#define TORRE_CONTROLE_CABINE_SLICES 10
#define TORRE_CONTROLE_CABINE_STACKS 10
#define TORRE_CONTROLE_CABINE_TRANSLACAO_X TORRE_CONTROLE_BASE_TRANSLACAO_X
#define TORRE_CONTROLE_CABINE_TRANSLACAO_Z 0.0  

static int rotx = 45;
static int roty = 0;

static float zoom = -1500.0;

// TODO: 
// 3) aviao
// 4) zoom in / zoom out

/**
 * Desenha cada port�a de embarque
 *
 * @param quantidades_portoes recebe a quantidade de port�es que ser�o criados para garantir o espa�amento
 * @param port�oo o n�mero do port�o pelo qual ser� impresso
 */
void desenhar_portao_embarque(int quantidades_portoes, int portao){
  glPushMatrix();

  // transla��o de Y
  float t_z = 
  	((PORTOES_ESCALONAMENTO_Z/quantidades_portoes) * portao) 
  		- ((quantidades_portoes/2) * (PORTOES_ESCALONAMENTO_Z/quantidades_portoes));

  glTranslatef (PORTAO_TRANSLACAO_X, CHAO_ALTURA + (PORTOES_ESCALONAMENTO_Y/2), t_z);
  glScalef (PORTAO_ESCALONAMENTO_X, PORTAO_ESCALONAMENTO_Y, PORTAO_ESCALONAMENTO_Z);
  glutWireCube (1.0);

  glPopMatrix();
}


/**
 * Desenha a torre de controle
 *
 * @param quantidade_galpoes recebe a quantidade de galpoes criados para gerar espa�aamento necess�rio para deixar a torre de lado
 */
void desenhar_torre_controle(int quantidade_galpoes){
  glPushMatrix();

  float 
  	t_z = - ((quantidade_galpoes/2) * (GALPAO_ESCALONAMENTO_Z * 2));
  
  glTranslatef (
	  (GLfloat) TORRE_CONTROLE_BASE_TRANSLACAO_X, 
	  (GLfloat) (CHAO_ALTURA + (TORRE_CONTROLE_BASE_ALTURA)), 
	  (GLfloat) t_z
  );
  glRotatef ((GLfloat) 90, 1.0, 0.0, 0.0);
  glutWireCylinder(
  	  (GLdouble) TORRE_CONTROLE_BASE_RAIO,
	  (GLdouble) TORRE_CONTROLE_BASE_ALTURA,
	  (GLint) TORRE_CONTROLE_BASE_SLICES,
	  (GLint) TORRE_CONTROLE_BASE_STACKS
  );

  glPopMatrix();
  
  glPushMatrix();  
  glTranslatef (
	  (GLfloat) TORRE_CONTROLE_CABINE_TRANSLACAO_X, 
	  (GLfloat) (CHAO_ALTURA + TORRE_CONTROLE_CABINE_ALTURA + TORRE_CONTROLE_BASE_ALTURA) , 
	  (GLfloat) t_z
  );
  glRotatef ((GLfloat) 90, 1.0, 0.0, 0.0);
  glutWireCylinder(
  	  (GLdouble) TORRE_CONTROLE_CABINE_RAIO,
	  (GLdouble) TORRE_CONTROLE_CABINE_ALTURA,
	  (GLint) TORRE_CONTROLE_CABINE_SLICES,
	  (GLint) TORRE_CONTROLE_CABINE_STACKS
  );

  glPopMatrix();
}


/**
 * Desenha os port�es onde haver� cada port�o de embarque
 */
void desenhar_portoes(){
  glPushMatrix();

  glTranslatef (PORTOES_TRANSLACAO_X, CHAO_ALTURA + (PORTOES_ESCALONAMENTO_Y/2), 0.0);
  glScalef (PORTOES_ESCALONAMENTO_X, PORTOES_ESCALONAMENTO_Y, PORTOES_ESCALONAMENTO_Z);
  glutWireCube(1.0);
  
  glPopMatrix();
  
  int
  	i, 
  	quantidade_portoes = 5;// deixei 5 por default, mas poder� ser mudado para quantos quiser
  
  for(i=0;i<quantidade_portoes;i++){
  	desenhar_portao_embarque(quantidade_portoes,i);
  }  
}

/**
 * Desenha um galp�o de acordo com os par�metros
 * 
 * @param t_x faz a transla��o do eixo X
 * @param t_y faz a transla��o do eixo Y
 * @param t_z faz a transla��o do eixo Z
 */
void desenhar_galpao(int quantidade_galpoes, int galpao){
  glPushMatrix();

  // transla��o de Y
  float t_z =  ((GALPAO_ESCALONAMENTO_Z + GALPAO_ESPACAMENTO) * galpao) - ((quantidade_galpoes/2) * GALPAO_ESCALONAMENTO_Z);

  glTranslatef (GALPAO_TRANSLACAO_X, CHAO_ALTURA + (GALPAO_ESCALONAMENTO_Y/2), t_z);
  glScalef (GALPAO_ESCALONAMENTO_X, GALPAO_ESCALONAMENTO_Y, GALPAO_ESCALONAMENTO_Z);
  glutWireCube (1.0);

  glPopMatrix();
}


/**
 * Desenha uma pista de acordo com os par�metros
 * 
 * @param t_x faz a transla��o do eixo X
 * @param e_z faz o escalonamento do eixto Z
 */
void desenhar_pista(float t_x, float e_z){
  glPushMatrix();

  glTranslatef (t_x, PISTA_TRANSLACAO_Y, PISTA_TRANSLACAO_Z);
  glScalef (PISTA_ESCALONAMENTO_X, PISTA_ESCALONAMENTO_Y, e_z);
  glutWireCube (1.0);

  glPopMatrix();
}

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  glRotatef ((GLfloat) rotx, 1.0, 0.0, 0.0);
  glRotatef ((GLfloat) roty, 0.0, 1.0, 0.0);
  
  glTranslatef (0.0, zoom, zoom);
  
  // congonhas tem duas pistas:
  // 1940x45 e 1495x45  
  desenhar_pista(-100.0,1940.0);
  desenhar_pista(100.0,1495.0);

  // galp�es/hagares
  int 
  	qtd_galpoes = 5,
  	i;  
  for(i= 0; i < qtd_galpoes;i++){
  	desenhar_galpao(qtd_galpoes,i);
  }  
  // Port?es onde ficar?o os port?es de embarque
  desenhar_portoes();
  
  // Onde ficar� a torre de controle
  desenhar_torre_controle(qtd_galpoes);

  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 5000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, -200.0, 0.0);
}
void keyboard(unsigned char key, int x, int y){
		
  switch (key) {
  case 'a':
  case 'A':
    roty = (roty + 2) % 360;
    glutPostRedisplay();
    break;
  case 'd':
  case 'D':
    roty = (roty - 2) % 360;
    glutPostRedisplay();
    break;
   case 'w':
   case 'W':
    rotx = (rotx + 1) % 360;
    glutPostRedisplay();
    break;
  case 's':
  case 'S':
    rotx = (rotx - 1) % 360;
    glutPostRedisplay();
    break;
  case 27:                                         // tecla Esc (encerra o programa)
	exit(0);
	break;
  }
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
	    switch(button) {
		// Button 3 == SCROLL UP and Button 4  == SCROLL DOWN
	    case 3:
	      zoom += 30.0;
	      glutPostRedisplay();
	      break;
	    case 4:
	      zoom -= 30.0;
	      glutPostRedisplay();
	      break;
	    default:
	      break;
	    }
	  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

