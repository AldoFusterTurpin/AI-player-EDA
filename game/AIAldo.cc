//ALDO FUSTER TURPIN
#include "Player.hh"
#include <list>
#include <set>
#include <map>
#include <vector>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Aldo


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */ 

    /*******************  BFS iteratiu *************************************/
    Dir bfs_granjers(const Pos& inici) { 
        //construim el camí fins arribar a la primera pos lliure i sense perill
        queue<Pos> frontera;
        frontera.push(inici);

        map<Pos, Pos> on_venim; //on_venim[p] conte (la direccio que hem pres
                                //des de l'anterior casella de p) per arribar a p
                                //(anterior casella es la del cami)
        on_venim[inici] = inici; 

        Dir direccio_presa;
        Pos actual;
        while (not frontera.empty()) { 
          actual = frontera.front(); 
          frontera.pop();

          if (not (posicio_es_meva(actual))) {
            break;
          }
          

          set<Dir> S {Left, Right, Top, Bottom};
          auto it = S.begin();
          for(int i = 0; i < S.size(); ++i) {
            direccio_presa = *it;
            ++it;
            auto seguent_pos = actual + direccio_presa;
            if ( (not(posicio_es_pared(seguent_pos))) and (not(posicio_ocupada_per_algu(seguent_pos))) and (not(posicio_amenacada_granjers(seguent_pos))) and (on_venim.find(seguent_pos) == on_venim.end())) {

              frontera.push(seguent_pos);   
              on_venim[seguent_pos] = actual;
            }
          }
        }  
        
        //ara hem de desfer el camí per trobar la 1a direccio presa
        Pos aux; //sera la bona
        while (actual != inici) {
          aux = actual;
          actual = on_venim[actual];
        }  

        //ara hem de buscar direccio a una de les 4 pos adjecents a inici
        if (inici + Right == aux) return Right;
        if (inici + Left == aux) return Left;
        if (inici + Top == aux) return Top;
        else return Bottom;
      }

      /***************** fi bfs iteratiu *************************************/


    Dir bfs_caballers(const Pos& inici) { 
        //construim el camí fins arribar a la primera pos lliure i sense perill
        queue<Pos> frontera;
        frontera.push(inici);

        map<Pos, Pos> on_venim; //on_venim[p] conte (la direccio que hem pres
                                //des de l'anterior casella de p) per arribar a p
                                //(anterior casella es la del cami)
        on_venim[inici] = inici; 

        Dir direccio_presa;
        Pos actual;
        //cerr << "empieza la fiesta: " << actual.i << " " << actual.j << endl;
        while (not frontera.empty()) { 
          actual = frontera.front(); 
          frontera.pop();

          if (posicio_ocupada_per_granjer_o_caballer_enemic(actual)) {
            break;
          }
          

          set<Dir> S {RT, Left, TL, Right, Top, LB,Bottom, BR};
          auto it = S.begin();
          for(int i = 0; i < S.size(); ++i) {
            direccio_presa = *it;
            ++it;
            auto seguent_pos = actual + direccio_presa;
            if ((not(posicio_es_pared(seguent_pos))) and (not(posicio_amenacada_caballers(seguent_pos))) and
             (on_venim.find(seguent_pos) == on_venim.end())) {
              frontera.push(seguent_pos);   
              on_venim[seguent_pos] = actual;
            }
          }
        }  
        
        //ara hem de desfer el camí per trobar la 1a direccio presa
        Pos aux; //sera la bona
        while (actual != inici) {
          aux = actual;
          actual = on_venim[actual];
        }  

        //ara hem de buscar direccio a una de les 4 pos adjecents a inici
        if (inici + Right == aux) return Right;
        if (inici + Left == aux) return Left;
        if (inici + Top == aux) return Top;
        if (inici + RT == aux) return RT;
        if (inici + TL == aux) return TL;
        if (inici + LB == aux) return LB;
        if (inici + BR == aux) return BR;
        else return Bottom;
      }
      /* fi bfs iteratiu *********************/
        


      Dir bfs_bruixes(const Pos& inici) { 
        //construim el camí fins arribar a la primera pos lliure i sense perill
        queue<Pos> frontera;
        frontera.push(inici);

        map<Pos, Pos> on_venim; //on_venim[p] conte (la direccio que hem pres
                                //des de l'anterior casella de p) per arribar a p
                                //(anterior casella es la del cami)
        on_venim[inici] = inici; 

        Dir direccio_presa;
        Pos actual;
        while (not frontera.empty()) { 
          actual = frontera.front(); 
          frontera.pop();

          if (posicio_caballer(actual)) {
            break;
          }
          

          set<Dir> S {Left, Right, Top, Bottom};
          auto it = S.begin();
          for(int i = 0; i < S.size(); ++i) {
            direccio_presa = *it;
            ++it;
            auto seguent_pos = actual + direccio_presa;
            if ( (not(posicio_es_pared(seguent_pos))) and (on_venim.find(seguent_pos) == on_venim.end())) {

              frontera.push(seguent_pos);   
              on_venim[seguent_pos] = actual;
            }
          }
        }  
        
        //ara hem de desfer el camí per trobar la 1a direccio presa
        Pos aux; //sera la bona
        while (actual != inici) {
          aux = actual;
          actual = on_venim[actual];
        }  

        //ara hem de buscar direccio a una de les 4 pos adjecents a inici
        if (inici + Right == aux) return Right;
        if (inici + Left == aux) return Left;
        if (inici + Top == aux) return Top;
        else return Bottom;
      }

      /***************** fi bfs iteratiu *************************************/





      bool esta_fora(const Pos& p){
        return p.i >= 37 or p.i < 0 or p.j >= 37 or p.j < 0;
      }

    //retorna cert si a la Pos p hi ha una pared
    bool posicio_es_pared(const Pos& p) {
      return (cell(p)).type == Wall;
    }

   //retorna cert si la Pos p esta buida
   bool posicio_no_conquerida(const Pos& p) {
    return (cell(p)).owner == -1;
   }

   bool posicio_ocupada_per_algu(const Pos& p) {
    return cell(p).id != -1;
  }

   bool posicio_embruixada(const Pos& p) {
    return (cell(p)).haunted;
   }   

   bool posicio_es_meva(const Pos& p) {
    return (cell(p)).owner == 0;
  }

  /*bool posicio_okay(const Pos& p) {
     return ((not(posicio_es_pared(p))) and (not(posicio_amenacada_granjers(p)) and (not(posicio_embruixada(p)))));
  }*/

  
  bool posicio_ocupada_per_granjer_o_caballer_enemic(const Pos& p) {
    auto cela = (cell(p));
    if (cela.id == -1) return false;
    int identificador = (cela.id);
    auto unitat = unit(identificador);
    if ((unitat.type == 0 or unitat.type ==1) and (unitat.player != 0)) {
      return true;
    }
    return false;
  }






  //retorna true si a p hi ha un caballer ENEMIC!
  bool posicio_caballer(const Pos& p){
    int identificador = (cell(p)).id;
    if (identificador == -1) return false;
    Unit u = unit(identificador);
    if (u.player == 0) return false; //ja que el caballer es meu
    return u.type == Knight;
  }

  /*retorna cert si la Pos p SÍ estarà amenaçada per una bruixa/caballer
  s'usa a bfs_granjers*/
   bool posicio_amenacada_granjers(const Pos& p) {
      set<Dir> S = {Bottom, BR, RT, TL, LB, Top, Left, Right};
      auto it = S.begin();
      for (int i = 0; i < S.size(); ++i) {
        if ((posicio_caballer(p + *it)) or  (posicio_embruixada(p + (*it)))) return true;
        ++it;
      }
      return false;
   }


   /*retorna cert si la Pos p SÍ estarà amenaçada per una bruixa/caballer
  s'usa a bfs_caballers*/
   bool posicio_amenacada_caballers(const Pos& p) {
      set<Dir> S = {Bottom, BR, RT, TL, LB, Top, Left, Right};
      auto it = S.begin();
      for (int i = 0; i < S.size(); ++i) {
        if ((posicio_embruixada(p + (*it)))) return true;
        ++it;
      }
      return false;
   }



//retorna la iésima Dir de S (pensant com si S fos un vector)
//i la borra de S
Dir donam_un(set<Dir>& S, int iesima) {
  int i = 1; 
  auto it = S.begin();
  while (i < iesima) {
    ++i; 
    ++it;
  }
  
    auto aux = *it;
    S.erase(it);
    return aux;  
}



  /*retorna la direccio que em de pendre desde p per anar a la 
  1ª casella que no perilli adjacent
  Actualitzem futures_pos_ocupades indicant que alguna unitat nostra es moura allà*/
  Dir explorar_al_voltant(const Pos& p, const int& diagonal_permited = 0){
        set<Dir> S = {Bottom, Left, Top, Right};
        int i = 0;
        Pos aux;
        while(i < S.size()) {
          auto direccio_prenem = donam_un(S, random(1,S.size())); 
          aux = p + direccio_prenem;
          if (not (posicio_es_pared(aux))) {
            return direccio_prenem;
          }
          
          ++i;
        } 
      //si no hem pogut trobar cap valida
      if (round() % 2 == 0) return Right;
      return Bottom;
  } 

    void move_witches(const vector<int>& w){
        for (auto x : w) command(x, bfs_bruixes(unit(x).pos));
    }

    void move_farmers(const vector<int>& f){
        for (auto x : f) command(x, bfs_granjers(unit(x).pos));
        
    }

    void move_knights(const vector<int>& k){
        for (auto x : k) command(x, bfs_caballers(unit(x).pos));
        
    }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_witches(witches(0));
    move_knights(knights(0));
    move_farmers(farmers(0));
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
