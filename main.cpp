#include <bits/stdc++.h>
#include <mapAlgo.hpp>
using namespace std;

int main(){
    Graph campus;

    // ===== Input Node (Lokasi) =====
    int jumlahNode;
    cout << "Masukkan jumlah lokasi: ";
    cin >> jumlahNode;
    cin.ignore();

    cout << "\n--- Input Lokasi ---\n";
    cout << "(Titik referensi = pojok ujung kiri kampus = 0, 0)\n\n";

    for(int i = 0; i < jumlahNode; i++){
        string nama;
        double x, y, elev;

        cout << "Lokasi ke-" << i+1 << ":\n";
        cout << "  Nama      : "; getline(cin, nama);
        cout << "  X (Kanan/Kiri) (meter) : "; cin >> x;
        cout << "  Y (Depan/Belakang) (meter) : "; cin >> y;
        cout << "  Elevasi (mdpl)   : "; cin >> elev;
        cin.ignore();
        cout << endl;

        campus.addNode(nama, x, y, elev);
    }

    // ===== Input Edge (Jalan) =====
    int jumlahEdge;
    cout << "--- Daftar Lokasi ---\n";
    for(int i = 0; i < campus.nodes.size(); i++){
        cout << "  [" << i << "] " << campus.nodes[i].name << "\n";
    }

    cout << "\nMasukkan jumlah jalan (edges): ";
    cin >> jumlahEdge;

    cout << "\n--- Input Jalan ---\n";
    for(int i = 0; i < jumlahEdge; i++){
        int from, to;
        cout << "Jalan ke-" << i+1 << ":\n";
        cout << "  Dari index : "; cin >> from;
        cout << "  Ke index   : "; cin >> to;

        campus.addEdge(from, to);
        campus.addEdge(to, from);

        cout << "  Jarak      : " << campus.hitungJarak(from, to) << " meter (otomatis)\n";
        cout << "  Slope      : " << campus.hitungSlope(from, to) << "% (otomatis)\n\n";
    }

    // ===== Pencarian Route =====
    string startName, goalName;
    cin.ignore();
    cout << "--- Pencarian Rute ---\n";
    cout << "Dari  : "; getline(cin, startName);
    cout << "Ke    : "; getline(cin, goalName);

    int start = campus.findNode(startName);
    int goal  = campus.findNode(goalName);

    if(start == -1 || goal == -1){
        cout << "Location not found!\n";
        return 1;
    }

    double slopeWeight;
    cout << "Slope weight (0-10 | Kecuraman Tidak Penting-Pilih Jalur Paling Landai): ";
    cin >> slopeWeight;

    vector<int> path = dijkstra(campus, start, goal, slopeWeight);

    cout << "\nRute terbaik dari " << startName << " ke " << goalName << ":\n";
    for(int node : path){
        // cout << campus.nodes[node].name << " (x=" << campus.nodes[node].x << ", y=" << campus.nodes[node].y << ")\n";
        if (node != path.back()){
            cout << campus.nodes[node].name << " --> ";
        }
        else{
            cout << campus.nodes[node].name << endl;
        }
        
    }

    return 0;
}