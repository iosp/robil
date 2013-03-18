package document.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import windows.designer.BTDesigner;

import document.Document;
import document.Parameters;

public class SaveXMLAction extends AbstractDesignerAction implements
		ActionListener {

	public SaveXMLAction(BTDesigner designer) {
		super(designer);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String fileName = null;

		if (e.getActionCommand().equals("file_save_as")) {
			fileName = Dialogs.saveFile("Save XML", "xml", "plan.xml",
					Parameters.path_to_plans);

		} else if (e.getActionCommand().equals("file_save")) {
			Document document = getActiveTab().document;
			fileName = document.getAbsoluteFilePath();
		}

		if (fileName == null) {
			return;
		}
		
		// savePlan(fileName);
		getActiveTab().document.save(fileName);
	}

	private void savePlan(String path) {
		// JOptionPane.showMessageDialog(null, "Error: not implemented",
		// "Save Plan",
		// JOptionPane.ERROR_MESSAGE);
		// return;
		getActiveTab().document.compile(path, true, true);
		// document.setCurrentWorkingFile(path);
	}
}
