/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package controller;

import View.ExamenP5View;
import deepspace.GameUniverse;
import deepspace.EnemyToUI;

/**
 *
 * @author leandrofdez
 */
public class ExamenP5Controller {
    
    private static final ExamenP5Controller instance = new ExamenP5Controller();
    private GameUniverse game;
    private ExamenP5View view;
    
    
    private ExamenP5Controller () {}
    
    public static ExamenP5Controller getInstance () {
      return instance;
    }
    
    public void setModelView (GameUniverse aGame, ExamenP5View aView) {
      game = aGame;
      view = aView;
    }
    
    public void start() {
        view.updateView();
        view.showView();
    }
    
    public EnemyToUI nextEnemy(){
        
        return game.nextEnemy();
    }
    
}
