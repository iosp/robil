package document.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import document.BTDesigner;
import document.Document;

/**
 * An abstract designer action listener, use it if your action listener utilize
 * any designer components
 * @author matan
 *
 */ 
public abstract class AbstractDesignerAction implements ActionListener{

	protected BTDesigner designer;
	
	public AbstractDesignerAction(BTDesigner designer) {
		this.designer = designer;
	}
	
	/**
	 * gets the currently active tab in designer
	 * @return
	 */
	public BTDesigner.DesignerTab getActiveTab() {
		// if no tab is currently selected, create a new one
//		if (designer.tabbedPane.getSelectedComponent() == null) {
		
		
//		if (designer.tabbedPane.getTabCount() == 0) {
//			designer.addNewDocumentTab(); 
//		}
//		designer.toolbar.setActiveDocument();
		return designer.getActiveTab();

	}
	
	@Override
	public void actionPerformed(ActionEvent e) {}

}
