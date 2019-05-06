/* 
 * File:   main.cpp
 * Author: marianasic
 *
 * Created on May 5, 2019, 9:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <istream>


using namespace std;

struct nodosplay{
    int clave;
    nodosplay* izq;
    nodosplay* der;
};


class arbolsplay {
public: 
    arbolsplay(){
        
    }
    
    nodosplay* insertar(int clave, nodosplay* raiz){
        static nodosplay* p = NULL;
        if(!p)
            p = nuevonodo(clave);
        else
            p -> clave = clave;
        
        if(!raiz){
            raiz = p;
            p = NULL;
            return raiz;
        }
        
        raiz = Splay(clave, raiz);
        
        if(clave < raiz -> clave){
            p -> izq = raiz -> izq;
            p -> der = raiz;
            raiz -> izq = NULL;
            raiz = p;
        }
        
        else if(clave > raiz -> clave){
            p -> der = raiz -> der;
            p -> izq = raiz;
            raiz -> der = NULL;
            raiz = p;
        }
        else
            return raiz;
        p = NULL;
        return raiz;
    }
    
    nodosplay* eliminar(int clave, nodosplay* raiz){
        nodosplay* tmp;
        if(!raiz)
            return NULL;
        raiz = Splay(clave, raiz);
        if(clave != raiz -> clave)
            return raiz;
        else{
            if(!raiz -> izq){
                tmp = raiz;
                raiz = raiz -> der;
            }else{
                tmp = raiz;
                raiz = Splay(clave, raiz -> izq);
                raiz -> der = tmp -> der;
            }
            
            free(tmp);
            return raiz;
        }
    }
    
    nodosplay* buscar(int clave, nodosplay* raiz){
        return Splay(clave, raiz);
    }
    
    
    nodosplay* nuevonodo(int clave){
        nodosplay* p = new nodosplay;
        if(!p){
            fprintf(stderr, "No se pudo crear el nodo \n");
            exit(1);
        }
        
        p -> clave = clave;
        p -> izq = p -> der = NULL;
        return p;
    }
    
    //rotacion zag
    nodosplay* rotacionder(nodosplay* n){
        nodosplay* tmp = n -> izq;
        n -> izq = tmp -> der;
        tmp -> der = n;
        return tmp;
    }
    
    //rotacion zig
    nodosplay* rotacionizq(nodosplay* n){
        nodosplay* tmp = n -> der;
        n -> der = tmp -> izq;
        tmp -> izq = n;
        return tmp;
    }
    
    //funcion en si de splay
    nodosplay* Splay(int clave, nodosplay* raiz){
        if(!raiz)
            return NULL;
        
        nodosplay cabeza;
        cabeza.izq = cabeza.der = NULL;
        //referencia de la cabeza
        nodosplay* maxizq = &cabeza;
        nodosplay* minder = &cabeza;
        
        while(1){
            if(clave < raiz -> clave){
                if(!raiz -> izq)
                    break;
                if(clave < raiz -> izq -> clave){
                    raiz = rotacionder(raiz);
                    if(!raiz -> izq)
                        break;
                }
                
                minder -> izq = raiz;
                minder = minder -> izq;
                raiz = raiz -> izq;
                minder -> izq = NULL;
            }
            else if(clave > raiz -> clave){
                if(!raiz -> der)
                    break;
                if(clave > raiz -> der -> clave){
                    raiz = rotacionizq(raiz);
                    if(!raiz -> der)
                        break;
                }
                
                maxizq -> der = raiz;
                maxizq = maxizq -> der;
                raiz = raiz -> der;
                maxizq -> der = NULL;
                
            }
            else
                break;
        }
        
        maxizq -> der = raiz -> izq;
        minder -> izq = raiz -> der;
        raiz -> izq = cabeza.der;
        raiz -> der = cabeza.izq;
        return raiz;
    }
    
    void inorden(nodosplay* raiz){
        if(raiz){
            inorden(raiz -> izq);
            cout << "clave: " << raiz -> clave;
            if(raiz -> izq)
                cout << " , " << raiz -> izq -> clave;
            if(raiz -> der)
                cout << " , " << raiz -> der -> clave;
            cout << "\n";
            inorden(raiz -> der);
        }
    }
    
    string nodosGV(nodosplay *quien){
        string r = "";
        int i, x;
        char c1[50] = "n";
	char c2[50];
        int num = quien->clave;
        sprintf(c2, "%d", num);
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c2[x] != '\0'; x++, i++)
		c1[i] = c2[x];
	c1[i+1] = '\0';
        
        char c3[50] = "[label=\"<izq> |<f> ";
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c3[x] != '\0'; x++, i++)
		c1[i] = c3[x];
	c1[i+1] = '\0';
        
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c2[x] != '\0'; x++, i++)
		c1[i] = c2[x];
	c1[i+1] = '\0';
        
        char c4[50] = " | <der>\"];\n";
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c4[x] != '\0'; x++, i++)
		c1[i] = c4[x];
	c1[i+1] = '\0';
        
        r = c1;
        
        return (r);
    }
    
    string nodoarbol(nodosplay *que){
        string res = "";
        int i, x;
        char c1[99999];
        string tmp = nodosGV(que);
        char *c2 = &tmp[0];
        sprintf(c1, "%s", c2);
        char c3[50] = "";
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c3[x] != '\0'; x++, i++)
		c1[i] = c3[x];
	c1[i+1] = '\0';
        
        if(que->izq != NULL){
            char c3[9999];
            string tmp1 = nodoarbol(que->izq);
            char *t = &tmp1[0];
            sprintf(c3, "%s", t);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c3[x] != '\0'; x++, i++)
                    c1[i] = c3[x];
            c1[i+1] = '\0';
            
            char c4[10] = "\"n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c4[x] != '\0'; x++, i++)
                    c1[i] = c4[x];
            c1[i+1] = '\0';
            
            char c5[10];
            int num1 = que->clave;
            sprintf(c5, "%d", num1);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c5[x] != '\0'; x++, i++)
                    c1[i] = c5[x];
            c1[i+1] = '\0';
            
            char c6[50] = "\":izq -> \"n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c6[x] != '\0'; x++, i++)
                    c1[i] = c6[x];
            c1[i+1] = '\0';
            
            char c7[10];
            int num2 = que->izq->clave;
            sprintf(c7, "%d", num2);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c7[x] != '\0'; x++, i++)
                    c1[i] = c7[x];
            c1[i+1] = '\0';
            
            char c8[50] = "\":f;\n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c8[x] != '\0'; x++, i++)
                    c1[i] = c8[x];
            c1[i+1] = '\0';
            
        }
        
        if(que->der != NULL){
            char c9[9999];
            string tmp2 = nodoarbol(que->der);
            char *t2 = &tmp2[0];
            sprintf(c9, "%s", t2);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c9[x] != '\0'; x++, i++)
                    c1[i] = c9[x];
            c1[i+1] = '\0';
            
            char c10[10] = "\"n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c10[x] != '\0'; x++, i++)
                    c1[i] = c10[x];
            c1[i+1] = '\0';
            
            char c11[10];
            int num3 = que->clave;
            sprintf(c11, "%d", num3);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c11[x] != '\0'; x++, i++)
                    c1[i] = c11[x];
            c1[i+1] = '\0';
            
            char c12[50] = "\":der -> \"n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c12[x] != '\0'; x++, i++)
                    c1[i] = c12[x];
            c1[i+1] = '\0';
            
            char c13[10];
            int num4 = que->der->clave;
            sprintf(c13, "%d", num4);
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c13[x] != '\0'; x++, i++)
                    c1[i] = c13[x];
            c1[i+1] = '\0';
            
            char c14[10] = "\":f;\n";
            for(i = 0; c1[i] != '\0'; i++);
            for(x = 0; c14[x] != '\0'; x++, i++)
                    c1[i] = c14[x];
            c1[i+1] = '\0';
        }
        
        res = c1;
        return (res);
    }
    
    
    string arbol(nodosplay* raiz){
        string respuesta = "";
        int i, x;
        
        char c1[999999] = "digraph g{\n label=\"Arbol SPL\"; edge [color = blue, splines = ortho];\nnode [shape = record, color=gold, height = .1];\n";
        string tmp = nodoarbol(raiz);
        char c2[99999];
        char *c3 = &tmp[0];
        sprintf(c2, "%s", c3);
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c3[x] != '\0'; x++, i++)
		c1[i] = c3[x];
	c1[i+1] = '\0';
        
        char c4[5] = "}\n";
	for(i = 0; c1[i] != '\0'; i++);
	for(x = 0; c4[x] != '\0'; x++, i++)
		c1[i] = c4[x];
	c1[i+1] = '\0';
        
        respuesta = c1;
        return (respuesta);
	
    }
    
    void dibujo(nodosplay* raiz){
        string respuesta = arbol(raiz);
        std::ofstream wf;
	wf.open("./Graphviz/splay.dot");
	wf << respuesta;
	wf.close();
	system("dot -Tpng ./Graphviz/splay.dot -o ./Graphviz/splay.png");
    }
    
};

/*
 * 
 */
int main(int argc, char** argv) {
    arbolsplay as;
    nodosplay *raiz;
    raiz = NULL;
    int opcion, aux;
    int tamanoarreglo;
    int j;
    std::ofstream wf;
    
    cout << " ######################## Bienvenido ########################" << endl;
    cout << "       Ingrese la cantidad de nodos a insertar en el Arbol Splay" << endl; 
    cin >> tamanoarreglo;
    int vector[tamanoarreglo];
    for(int i = 0; i < tamanoarreglo; i++){
        cout << "Ingrese el nodo a insertar en la posicion " << i + 1 << endl;
        int tmp;
        cin >> tmp;
        vector[i] = tmp;
    }

    for(int i = 0; i < tamanoarreglo; i++){
        raiz = as.insertar(vector[i], raiz);
    }

    while(1){
        
        cout << "                     OPERACIONES VALIDAS                  " << endl;
        cout << "       1.  Mostrar " << endl;
        cout << "       2.  Eliminar" << endl;
        cout << "       3.  Buscar" << endl;
        cout << "       4.  Graficar Arbol Splay" << endl;
        cout << "       5.  Graficar Arreglo" << endl;
        cout << "       6.  Salir" << endl;
        cout << "                  INGRESE LA OPCION DESEADA " << endl;
        cin >> opcion;
        switch(opcion){
            //insertar
            case 1:
                as.inorden(raiz);
                //cout << as.arbol(raiz) << endl;
                break;
            //eliminar
            case 2:
                cout << "       Ingrese la clave que desea eliminar " << endl;
                cin >> aux;
                raiz = as.eliminar(aux, raiz);
                cout << "   Nodos Actuales  " << endl;
                as.inorden(raiz);
                break;
            //buscar
            case 3:
                cout << "       Ingrese la clave que desea buscar " << endl;
                cin >> aux;
                raiz = as.buscar(aux, raiz);
                cout << "   Nodos Actuales " << endl;
                as.inorden(raiz);
                break;
            //graficar spl
            case 4:
                as.dibujo(raiz);
                break;
            //graficar arreglo
            case 5:
                
            wf.open("./Graphviz/arr.dot");
            wf << "digraph g{" << endl;
            wf << " rankdir = LR;" << endl;
            wf << " label=\"Arreglo de Entrada\";" << endl;
            wf << "edge [color = lightblue, splines = ortho];\n";
            wf << "node [shape = record, style = filled, fillcolor=lavender, height = .1];\n";
            for(j = 0; j < tamanoarreglo; j++){
                wf << "n" << j << "[label = \""<< vector[j] << "\"];" << endl;
                if(j != (tamanoarreglo - 1)){
                    wf << "n" << j << "-> n" << j+1 << ";" << endl;
                }
            }
            wf << "}";
            wf.close();
            system("dot -Tpng ./Graphviz/arr.dot -o ./Graphviz/arr.png");
            
                break;
            //salir
            case 6:
                exit(1);
            default:
                cout << "           OPCION INVALIDA :c " << endl;
        }
    }
    
    cout << "\n";
    
    return 0;
}


