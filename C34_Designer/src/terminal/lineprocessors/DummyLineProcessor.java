package terminal.lineprocessors;

public class DummyLineProcessor implements LineProcessor {

	public DummyLineProcessor() {}

	@Override
	public void onStart() {}

	@Override
	public void onNewLine(String line) {}

	@Override
	public void onEnd() {}

}
