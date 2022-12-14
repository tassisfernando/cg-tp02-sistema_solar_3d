
//*****************************************************
//
// Exemplo3DComZoomEPan.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// desenha um "torus" e permite fazer: zoom in e
// zoom out quando os botões do mouse são pressionados
// (utiliza a projeção perspectiva); e pan quando as
// teclas page up, page down, seta para cima, seta para
// baixo, seta para esquerda e seta para direita são
// pressionadas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objet

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


GLfloat angle, fAspect, rotX, rotY;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ;
GLfloat angleRotate = 0;
GLfloat a, b, c;

static int slices = 20;
static int stacks = 20;

// Funcao para desenhar linhas
void desenhaTerreno()
{
	float L = 500.0;
	float incr = 10.0;
	float y = 0.2;
	glColor3f(0.0f, 0.0f, 0.0f);

	for (float i = -L; i <= L; i += incr)
	{
	    glBegin(GL_LINES);
            // Verticais
            glVertex3f(i,y,-L);
            glVertex3f(i,y,L);

            // Horizontais
            glVertex3f(-L,y,i);
            glVertex3f(L,y,i);
		glEnd();
	}
}

void DesenhaJupiter() {
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
            glRotated(angleRotate*1.2, 0, 1, 0); // translação
            glPushMatrix();
                glTranslated(-95, 40, 0); // manda pra órbita
                glRotated(angleRotate*1.7, 0.0f, 0.0f, 1.0f); // rotação
                glutSolidSphere(6,slices,stacks);
            glPopMatrix();
    glPopMatrix();
}

void DesenhaMarte() {
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
            glRotated(angleRotate*1.2, 0, 1, 0); // translação
            glPushMatrix();
                glTranslated(-95, 40, 0); // manda pra órbita
                glRotated(angleRotate*1.7, 0.0f, 0.0f, 1.0f); // rotação
                glutSolidSphere(6,slices,stacks);
            glPopMatrix();
    glPopMatrix();
}

void DesenhaTerra() {
    glColor3f(0.0f, 0.0f, 1.0f);

    glPushMatrix();
            glRotated(angleRotate*1.4, 0, 1, 0); // translação
            glPushMatrix();
                glTranslated(80, 40, 0); // manda pra órbita
                glRotated(angleRotate*1.6, 0.0f, 0.0f, 1.0f); // rotação
                glutSolidSphere(6,slices,stacks);
            glPopMatrix();
    glPopMatrix();
}

void DesenhaVenus() {
    glColor3f(1.0f, 0.0f, 1.0f);

    glPushMatrix();
            glRotated(angleRotate*1.1, 0, 1, 0); // translação
            glPushMatrix();
                glTranslated(-65, 40, 0); // manda pra órbita
                glRotated(angleRotate*1.6, 0.0f, 0.0f, 1.0f); // rotação
                glutSolidSphere(5,slices,stacks);
            glPopMatrix();
    glPopMatrix();
}

void DesenhaMercurio() {
    glColor3f(1.0f, 0.0f, 0.5f);

    glPushMatrix();
            glRotated(angleRotate, 0, 1, 0); // translação
            glPushMatrix();
                glTranslated(50, 40, 0); // manda pra órbita
                glRotated(angleRotate*1.5, 0.0f, 0.0f, 1.0f); // rotação
                glutSolidSphere(3,slices,stacks);
            glPopMatrix();
    glPopMatrix();
}

void DesenhaSol() {
    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
        glRotated(angleRotate, 0, 1, 0);
        glTranslated(0,40,0);
        glutSolidSphere(20,slices,stacks);
    glPopMatrix();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    //desenhaTerreno();

	DesenhaSol();

	DesenhaMercurio();

	DesenhaVenus();

	DesenhaTerra();

	DesenhaMarte();

	DesenhaJupiter();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao()
{
    // Luz 0
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4]={0.0, 50.0, 0.0, 1.0};
    GLfloat posicaoLuz1[4] = {a, b, c, 1.0};
    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;
    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
    // Define os parâmetros da luz de número 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador, do alvo e do vetor up
	gluLookAt(deslocamentoX,deslocamentoY,deslocamentoZ,
		0,0,0,
		0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();

    DefineIluminacao();
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		// desloca o volume de visualização para cima
								deslocamentoY -= 2;
								break;
		case GLUT_KEY_DOWN:		// desloca o volume de visualização para baixo
								deslocamentoY += 2;
								break;
		case GLUT_KEY_LEFT:		// desloca o volume de visualização para o lado esquerdo
								deslocamentoX += 2;
								break;
		case GLUT_KEY_RIGHT:	// desloca o volume de visualização para o lado direito
								deslocamentoX -= 2;
								break;
		case GLUT_KEY_PAGE_UP:	// desloca o volume de visualização para frente
								deslocamentoZ -= 2;
								break;
		case GLUT_KEY_PAGE_DOWN:// desloca o volume de visualização para trás
								deslocamentoZ += 2;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback chamada quando são notificados os eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void Anima(int value){
    angleRotate += 1;
    glutPostRedisplay();
    glutTimerFunc(10,Anima, 1);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita a luz de número 1
    glEnable(GL_LIGHT1);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=60;

	// Inicializa as variáveis utilizadas para implementação
	// da operação de pan
	deslocamentoX = 0.0f;
	deslocamentoY = 110.0f;
	deslocamentoZ = 150.0f;
}

// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(1000,1000);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Sistema solar 3d");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback que gerencia os eventos do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	glutTimerFunc(100, Anima, 1);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
