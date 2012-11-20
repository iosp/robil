package document;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.management.Descriptor;
import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import document.listeners.CompileAction;
import document.listeners.LoadAndOpenAction;
import document.listeners.ModifyAction;
import document.listeners.NewWindowAction;
import document.listeners.OpenFileAction;
import document.listeners.OpenTerminalAction;
import document.listeners.PointAction;
import document.listeners.PropertiesAction;
import document.listeners.RemoveAction;
import document.listeners.RunAction;
import document.listeners.SaveImageAction;
import document.listeners.SaveXMLAction;
import document.listeners.ToolAction;

public class Menubar extends JMenuBar {

	public Menubar(BTDesigner designer) {
		add(buildFileMenu(designer));
		add(buildEditMenu(designer));
		add(buildWindowMenu(designer));
	}

	private JMenu buildFileMenu(BTDesigner designer) {
		/* build File Menu */

		JMenu menuFile = new JMenu("File");

		ImageIcon icon;
		
		menuFile.setMnemonic(KeyEvent.VK_F);

		// open file
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/open.png"));
		JMenuItem menuItemOpen = new JMenuItem("Open", KeyEvent.VK_O);
		menuItemOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1,
				ActionEvent.ALT_MASK));
		menuItemOpen.setToolTipText("open file");
		menuItemOpen.setActionCommand("file_open");
		menuItemOpen.setIcon(icon);
		menuItemOpen.addActionListener(new OpenFileAction(designer));
		menuFile.add(menuItemOpen);

		// load and open
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/load_open.png"));
		JMenuItem menuItemLoadAndOpen = new JMenuItem("Load and Open",
				KeyEvent.VK_L);
		menuItemLoadAndOpen.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_2, ActionEvent.ALT_MASK));
		menuItemLoadAndOpen.setToolTipText("load and open file");
		menuItemLoadAndOpen.setActionCommand("file_load_and_open");
		menuItemLoadAndOpen.addActionListener(new LoadAndOpenAction(designer));
		menuItemLoadAndOpen.setIcon(icon);
		menuFile.add(menuItemLoadAndOpen);

		// save
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/save.png"));
		JMenuItem menuItemSave = new JMenuItem("Save", KeyEvent.VK_S);
		menuItemSave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_3,
				ActionEvent.ALT_MASK));
		menuItemSave.setToolTipText("save file");
		menuItemSave.setActionCommand("file_save");
		menuItemSave.setIcon(icon);
		menuItemSave.addActionListener(new SaveXMLAction(designer));
		// menuItemSave.addActionListener(listener);
		menuFile.add(menuItemSave);

		// save as
		JMenuItem menuItemSaveAs = new JMenuItem("Save As...", KeyEvent.VK_A);
		menuItemSaveAs.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_4,
				ActionEvent.ALT_MASK));
		menuItemSaveAs.setToolTipText("save file as");
		menuItemSaveAs.setActionCommand("file_save_as");
		menuItemSaveAs.addActionListener(new SaveXMLAction(designer));
		menuFile.add(menuItemSaveAs);

		// save image
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/save_image.png"));
		JMenuItem menuItemSaveImage = new JMenuItem("Save Image", KeyEvent.VK_I);
		menuItemSaveImage.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_5,
				ActionEvent.ALT_MASK));
		menuItemSaveImage
				.setToolTipText("creates PNG image and saves it locally");
		menuItemSaveImage.setActionCommand("file_save_image");
		menuItemSaveImage.setIcon(icon);
		menuItemSaveImage.addActionListener(new SaveImageAction(designer));
		menuFile.add(menuItemSaveImage);

		// compile
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/compile.png"));
		JMenuItem menuItemCompile = new JMenuItem("Compile");
		menuItemCompile.setMnemonic(KeyEvent.VK_C);
		menuItemCompile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_6,
				ActionEvent.ALT_MASK));
		menuItemCompile
				.setToolTipText("validates current plan and if plan is valid, saves it");
		menuItemCompile.addActionListener(new CompileAction(designer));
		menuItemCompile.setIcon(icon);
		menuFile.add(menuItemCompile);

		// compile and upload
		JMenuItem menuItemCompileAndUpload = new JMenuItem(
				"Compile And Upload", KeyEvent.VK_U);
		menuItemCompileAndUpload.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_7, ActionEvent.ALT_MASK));
		menuItemCompileAndUpload
				.setToolTipText("validates current plan and if plan is valid uploads it to remote host (C34_Executer’s host)");
		// menuItemCompileAndUpload.addActionListener(listener);
		menuFile.add(menuItemCompileAndUpload);

		// run
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/play.png"));
		JMenuItem menuItemRun = new JMenuItem("Run", KeyEvent.VK_R);
		menuItemRun.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_8,
				ActionEvent.ALT_MASK));
		menuItemRun.setIcon(icon);
		menuItemRun
				.setToolTipText("validates current plan, uploads it to temporal remote file on C34_Executer’s host and runs it");
		menuItemRun.addActionListener(new RunAction(designer));
		menuFile.add(menuItemRun);

		// test
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/test.png"));
		JMenuItem menuItemTest = new JMenuItem("Test", KeyEvent.VK_T);
		menuItemTest.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_9,
				ActionEvent.ALT_MASK));
		menuItemTest.setIcon(icon);
		menuItemTest
				.setToolTipText("validates current plan, saves it to a temporal local file and runs it in mode of logic simulation");
		// menuItemTest.addActionListener(listener);
		menuFile.add(menuItemTest);

		// properties
		icon = new ImageIcon(getClass().getClassLoader().getResource(
				"icons/settings.png"));
		JMenuItem menuItemProperties = new JMenuItem("Properties",
				KeyEvent.VK_P);
		menuItemProperties.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P,
				ActionEvent.ALT_MASK));
		menuItemProperties.setToolTipText("open properties dialog");
		menuItemProperties.setActionCommand("open_properties_dialog");
		menuItemProperties.addActionListener(new PropertiesAction());
		menuItemProperties.setIcon(icon);
		menuFile.add(menuItemProperties);

		return menuFile;
	}

	private JMenu buildEditMenu(BTDesigner designer) {
		JMenu menu = new JMenu("Edit");

		menu.setMnemonic(KeyEvent.VK_E);
		menu.add(buildToolsMenu(designer));
		menu.add(buildElementsCreatorMenu(designer));

		return menu;
	}

	private JMenu buildToolsMenu(BTDesigner designer) {
		JMenu menu = new JMenu("Tools");
		menu.setMnemonic(KeyEvent.VK_T);

		// remove
		JMenuItem menuItemRemove = new JMenuItem("Remove", KeyEvent.VK_R);
		menuItemRemove.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1,
				ActionEvent.ALT_MASK));
		menuItemRemove.setToolTipText("sets mode of selector to remove");
		menuItemRemove.addActionListener(new RemoveAction(designer));
		menu.add(menuItemRemove);

		// modify
		JMenuItem menuItemModify = new JMenuItem("Modify", KeyEvent.VK_M);
		menuItemModify.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_2,
				ActionEvent.ALT_MASK));
		menuItemModify.setToolTipText("sets mode of selector to modify");
		menuItemModify.addActionListener(new ModifyAction(designer));
		menu.add(menuItemModify);

		// move
		JMenuItem menuItemMove = new JMenuItem("Move", KeyEvent.VK_V);
		menuItemMove.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_3,
				ActionEvent.ALT_MASK));
		menuItemMove.setToolTipText("sets mode of selector to move");
		menuItemMove.addActionListener(new PointAction(designer));
		menu.add(menuItemMove);

		return menu;
	}

	private JMenu buildElementsCreatorMenu(BTDesigner designer) {
		JMenu menu = new JMenu("Elements Creator");
		menu.setMnemonic(KeyEvent.VK_C);

		// task
		JMenuItem menuItemTask = new JMenuItem("Task", KeyEvent.VK_T);
		menuItemTask.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1,
				ActionEvent.ALT_MASK));
		menuItemTask.setToolTipText("sets mode of selector to create tasks");
		menuItemTask.addActionListener(new ToolAction(designer,
				designer.toolbar.creators.get(0)));
		menu.add(menuItemTask);

		// arrow
		JMenuItem menuItemArrow = new JMenuItem("Arrow", KeyEvent.VK_A);
		menuItemArrow.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_2,
				ActionEvent.ALT_MASK));
		menuItemArrow.setToolTipText("sets mode of selector to create arrows");
		menuItemArrow.addActionListener(new ToolAction(designer,
				designer.toolbar.creators.get(1)));
		menu.add(menuItemArrow);

		// decorator
		JMenuItem menuItemDecorator = new JMenuItem("Decorator", KeyEvent.VK_D);
		menuItemDecorator.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_3,
				ActionEvent.ALT_MASK));
		menuItemDecorator
				.setToolTipText("sets mode of selector to create decorators");
		menuItemDecorator.addActionListener(new ToolAction(designer,
				designer.toolbar.creators.get(2)));
		menu.add(menuItemDecorator);

		// joint
		JMenuItem menuItemJoint = new JMenuItem("Joint", KeyEvent.VK_J);
		menuItemJoint.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_4,
				ActionEvent.ALT_MASK));
		menuItemJoint
				.setToolTipText("sets mode of selector to create joint points on arrows");
		menuItemJoint.addActionListener(new ToolAction(designer,
				designer.toolbar.creators.get(3)));
		menu.add(menuItemJoint);

		return menu;
	}

	private JMenu buildWindowMenu(BTDesigner designer) {
		JMenu menu = new JMenu("Window");
		menu.setMnemonic(KeyEvent.VK_W);

		// new
		JMenuItem menuItemNew = new JMenuItem("New", KeyEvent.VK_N);
		menuItemNew.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_1,
				ActionEvent.ALT_MASK));
		menuItemNew.setToolTipText("creates new instance of BTDesigner");
		menuItemNew.addActionListener(new NewWindowAction(designer));
		menu.add(menuItemNew);

		// open terminal
		JMenuItem menuItemOpenTerminal = new JMenuItem("Open Terminal",
				KeyEvent.VK_T);
		menuItemOpenTerminal.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_2, ActionEvent.ALT_MASK));
		menuItemOpenTerminal.setToolTipText("opens ROS terminal window");
		menuItemOpenTerminal.addActionListener(new OpenTerminalAction());
		menu.add(menuItemOpenTerminal);

		// open log console
		JMenuItem menuItemOpenLogConsole = new JMenuItem("Open Log Console",
				KeyEvent.VK_L);
		menuItemOpenLogConsole.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_3, ActionEvent.ALT_MASK));
		menuItemOpenLogConsole.setToolTipText("opens log history dialog");
		menu.add(menuItemOpenLogConsole);

		// about
		JMenuItem menuItemAbout = new JMenuItem("About", KeyEvent.VK_B);
		menuItemAbout.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_4,
				ActionEvent.ALT_MASK));
		menuItemAbout.setToolTipText("About the software");
		menu.add(menuItemAbout);

		return menu;
	}

}
