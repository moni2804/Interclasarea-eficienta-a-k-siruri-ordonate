# Interclasarea-eficienta-a-k-siruri-ordonate 
Acest cod implementează un **algoritm eficient \( O(n \log k) \) pentru interclasarea a \( k \) liste sortate** utilizând un **min-heap**.  

---

### **Ce Face Codul:**
1. **Generare de Liste Sortate:**  
   - Se creează \( k \) liste înlănțuite, fiecare sortată în mod ascendent.
   - Listele sunt generate aleatoriu, cu dimensiuni diferite, astfel încât să conțină în total \( n \) elemente.

2. **Interclasare cu Min-Heap:**  
   - Se construiește un **min-heap** din primele elemente ale fiecărei liste.  
   - Se extrage cel mai mic element și se înlocuiește cu următorul element din lista din care a fost extras.  
   - Se ajustează heap-ul pentru a menține proprietatea de min-heap.  
   - Se repetă procesul până la golirea heap-ului.  
   - Elementele rezultate sunt salvate într-o coadă.

3. **Evaluare Statistică:**  
   - Se măsoară performanța algoritmului variind **\( k \)** și **\( n \)**.  
   - Se rulează de mai multe ori pentru medierea rezultatelor.  
   - Se generează grafice cu numărul de **comparații** și **atribuiri** efectuate.  

4. **Demo pentru Corectitudine:**  
   - Se creează un set mic de liste sortate \( (n=20, k=4) \).  
   - Se interclasează și se afișează rezultatul pentru verificare vizuală.  

---

### **Complexitatea Algoritmului:**  
- **Construirea heap-ului:** \( O(k) \)  
- **Extrageri și rearanjare în heap:** \( O(n \log k) \)  
- **Complexitate totală:** \( O(n \log k) \)  

---

### **Cum se Rulează Codul:**  
- **Pentru testarea corectitudinii:** Se decomentează `demo(20,4);` în `main()`.  
- **Pentru testarea performanței:** Se rulează `perf();` pentru generarea de grafice.  
