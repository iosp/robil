package elements;

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Composite;
import java.awt.Graphics2D;
import java.util.Map;

public class Tooltip extends GElement {

	public enum ToolTipDesign {
		Default,
		DebugInfo,
		RuntimeInfo
	}
	
	@SuppressWarnings("unused")
	private String _title;
	private String _message;
	private final GElement _parent;
	private final ToolTipDesign _design;

	private Vec _textPosition = new Vec(0, 0);

	public Tooltip(GElement parent, ToolTipDesign design) {
		this._parent = parent;
		this._title = "";
		this._message = "";
		this._design = design;
	}
	
	public Tooltip(GElement parent) {
		this(parent, ToolTipDesign.Default);
	}
	
	@Override
	public GElement clone() {
		Tooltip tooltip = new Tooltip(this._parent, this._design);
		tooltip._message = new String(this._message);
		tooltip._textPosition = this._textPosition;
		tooltip._title = new String(this._title);
		return tooltip;
	}

	@Override
	public void cloneReconnect(Map<GElement, GElement> link) {

	}

	private void drawMultiLineString(Graphics2D g, String string, int x, int y) {
		for (String line : string.split("\n")) {
			Color originalColor = g.getColor();
			
			if (line.contains("$RED$")) 
				g.setColor(Color.RED);
			
			if (line.contains("$GREEN$"))
				g.setColor(Color.GREEN);
			
			if (line.contains("$BLUE$"))
				g.setColor(Color.BLUE);
			
			// Replace colors declarations:
			// 		$RED$, $BLUE$, $GREEN$
			g.drawString(line.replaceAll("\\$.*?\\$", ""), x, y += g.getFontMetrics().getHeight());
			
			g.setColor(originalColor);
		}
	}

	private int getLinesCountHeight(String string) {
		return string.split("\n").length;
	}

	private int getMaxLineWidth(Graphics2D g, String string) {
		double maxWidth = 0;

		for (String line : string.split("\n")) {
			if (maxWidth < getTextSize(g, line).getWidth())
				maxWidth = getTextSize(g, line).getWidth();
		}

		return (int) maxWidth;
	}

	@Override
	public void modify() {
	}

	@Override
	public void paint(Graphics2D g) {
		
		if (this._message.trim().equals(""))
			return;
		
		updatePosition(g);

		Composite oldComposite = g.getComposite();

		AlphaComposite ac = AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.8F);
		g.setComposite(ac);
		
		switch (_design) {
		case Default:
			g.setColor(Color.BLACK);
			g.fillRoundRect((int) this.property.loc.x, (int) this.property.loc.y, (int) this.property.size.x, (int) this.property.size.y, 10, 10);
			g.setColor(Color.WHITE);
			drawMultiLineString(g, this._message, (int) this._textPosition.x, (int) this._textPosition.y);
			break;
		case DebugInfo:
			g.setColor(Color.WHITE);
			g.fillRoundRect((int) this.property.loc.x, (int) this.property.loc.y, (int) this.property.size.x, (int) this.property.size.y, 10, 10);
			g.setColor(Color.BLACK);
			drawMultiLineString(g, this._message, (int) this._textPosition.x, (int) this._textPosition.y);
			break;
		case RuntimeInfo:
			g.setColor(Color.YELLOW);
			g.fillRoundRect((int) this.property.loc.x, (int) this.property.loc.y, (int) this.property.size.x, (int) this.property.size.y, 10, 10);
			g.setColor(Color.BLACK);
			drawMultiLineString(g, this._message, (int) this._textPosition.x, (int) this._textPosition.y);
			break;
		}
		
		g.setComposite(oldComposite);
	}

	public void setMessage(String title, String message) {
		this._title = "";
		this._message = (title.trim().length() > 0 ? title + ":\n" : "") + message;
	}
	
	public void setMessage(String message) {
		this._title = "";
		this._message = message;
	}
	
	public void setWordHighlighting(String word, Color color) {
		
	}

	public void updatePosition(Graphics2D g) {
		// Box location & dimensions
		this.property.loc.x = this._parent.getLocation().getX();
		this.property.loc.y = this._parent.getLocation().getY() + 27
				* this._parent.getView().zoom;

		this.property.size.x = getMaxLineWidth(g, this._message) + 40
				* this._parent.getView().zoom;
		this.property.size.y = getTextSize(g, this._message).getHeight()
				* getLinesCountHeight(this._message) + 10
				* this._parent.getView().zoom;

		// Text location
		this._textPosition.x = this.property.loc.x + 10
				* this._parent.getView().zoom;
		this._textPosition.y = this.property.loc.y + 2
				* this._parent.getView().zoom;
	}

}
