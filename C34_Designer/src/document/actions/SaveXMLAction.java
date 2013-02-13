package document.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JDialog;
import javax.swing.JOptionPane;

import document.BTDesigner;
import document.Document;
import document.Parameters;

public class SaveXMLAction extends AbstractDesignerAction implements ActionListener {
	
	private void savePlan(String path) {
//		JOptionPane.showMessageDialog(null, "Error: not implemented", "Save Plan",
//				JOptionPane.ERROR_MESSAGE);
//		return;
		getActiveTab().doc.compile(path);
//		document.setCurrentWorkingFile(path);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		String fileName = null;
		
		if (e.getActionCommand().equals("file_save_as")) {
			fileName = Dialogs.saveFile("Save XML", "xml", "plan.xml", Parameters.path_to_plans);
			
		} else if (e.getActionCommand().equals("file_save")) {
			Document document = getActiveTab().doc;
			fileName = document.getAbsoluteFilePath();
		}
		
		if (fileName == null) {
			return;
		}			
		savePlan(fileName);
		
	}

	public SaveXMLAction(BTDesigner designer){
		super(designer);
	}	
}
