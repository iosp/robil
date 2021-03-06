/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pathplanning;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;

/**
 *
 * @author dan
 */
public class MapPanel extends javax.swing.JPanel {

    ArrayList<MapBoard.Frame> frames = null;
    int frameIndex = 0;
    
    
    /**
     * Creates new form MapPanel
     */
    public MapPanel(ArrayList<MapBoard.Frame> frames) {
        this.frames = frames;
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

    void setFrameIndex(int findex) {
        frameIndex = findex;
    }
    
    
    @Override
    public void paint(Graphics g) {
        g.setColor(Color.WHITE);
        g.fillRect(0,0,getWidth(), getHeight());
        if(frames.size()==0) return;
        if(frameIndex<0 || frameIndex>=frames.size())return;
        MapBoard.Frame frame = frames.get(frameIndex);
        if(frame == null) return;
        
        frame.paint((Graphics2D)g, getSize());
    }
    
    
    
}
