package document.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import document.BTDesigner;

public class ExportTasksAction extends AbstractDesignerAction implements ActionListener {

	public ExportTasksAction(BTDesigner designer) {
		super(designer);
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		
		if (designer.getActiveTab() != null && designer.getActiveTab().doc != null) {
			String fileName = Dialogs.saveFile("Export tasks", "");
			
			if (!fileName.equals(""))
				designer.getActiveTab().doc.exportTasks(fileName);
		}
	}

}
