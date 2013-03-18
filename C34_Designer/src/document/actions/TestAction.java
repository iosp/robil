package document.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import windows.designer.BTDesigner;


public class TestAction extends AbstractDesignerAction implements
		ActionListener {

	public TestAction(BTDesigner designer) {
		super(designer);
	}

	@Override
	public void actionPerformed(ActionEvent a) {
		getActiveTab().document.test();
	}
}