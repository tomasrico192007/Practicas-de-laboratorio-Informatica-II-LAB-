#include <iostream>
#include "red.h"
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    red net;
    string filename;

    if (argc >= 2) {
        filename = argv[1];
        if (!net.loadFromFile(filename)) return 1;
    } else {
        cout << "Coloque el archivo de topología tipo txt";
        cin >> filename;
        if (!net.loadFromFile(filename)) return 1;
    }

    cout << "Topología cargada desde" << filename << ".\n\n";

    cout << "Los comandos disponibles son:";
    cout << "  lista                         - listar routers";
    cout << "  tabla <R>                    - mostrar tabla de enrutamiento de R";
    cout << "  costo <ORIG> <DEST>           - mostrar costo solo";
    cout << "  path <ORIG> <DEST>           - mostrar camino y costo";
    cout << "  añadirrouter <R>                - agregar router (sin enlaces)";
    cout << "  removerrouter <R>             - eliminar router";
    cout << "  añadircamino <A> <B> <cost>       - agregar o actualizar enlace";
    cout << "  salir                         - salir";

    string cmd;
    while (true) {
        cout << "> ";
        if (!(cin >> cmd)) break;

        if (cmd == "list") net.listRouters();
        else if (cmd == "table") {
            string r; cin >> r;
            net.showRouterTable(r);
        } else if (cmd == "cost") {
            string o,d; cin >> o >> d;
            auto res = net.getCostAndPath(o,d);
            if (res.first < 0) cout << "No se puede alcanzar o el router no existe";
            else cout << "El costo minimo de " << o << " a " << d << " = " << res.first << "\n\n";
        } else if (cmd == "path") {
            string o,d; cin >> o >> d;
            auto res = net.getCostAndPath(o,d);
            if (res.first < 0) cout << "No se puede alcanzar o el router no existe";
            else {
                cout << "El camino de" << o << " a " << d << ": ";
                for (size_t i=0;i<res.second.size();++i) {
                    if (i) cout << " -> ";
                    cout << res.second[i];
                }
                cout << "Tiene un costo de = " << res.first << ")\n\n";
            }
        } else if (cmd == "addrouter") {
            string r; cin >> r;
            net.addRouter(r);
            cout << "El router " << r << "  se agrego";
        } else if (cmd == "removerouter") {
            string r; cin >> r;
            net.removeRouter(r);
            cout << "El router " << r << " se removido";
        } else if (cmd == "addedge") {
            string a,b; int c; cin >> a >> b >> c;
            net.addOrUpdateEdge(a,b,c);
            cout << "Enlace" << a << "-" << b << "Ya se agrego la actualizacion";
        } else if (cmd == "exit") {
            cout << "Ya esta saliendo";
            break;
        } else {
            cout << "Comando no reconocido";
        }
    }

    return 0;
}
