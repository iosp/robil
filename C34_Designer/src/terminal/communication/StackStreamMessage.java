package terminal.communication;

/**
 * Message received from stack-stream
 * @author blackpc
 *
 */
public class StackStreamMessage implements IMessage<StackStreamMessage> {

	public enum ChangeType {
		TaskStarted(0),
		TaskFinished(1);

		private int _code;
		
		ChangeType(int code) {
			_code = code;
		}
		
		public int getCode() {
			return _code;
		}
		
		public static ChangeType typeOf(int code) {
			if (code == 0)
				return ChangeType.TaskStarted;
			else 
				return ChangeType.TaskFinished;
		}
	}
	
	public enum TaskFinishReason {
		Success("SUCCESS"),
		Failure("FAILURE");
		
		private String _name;
		private TaskFinishReason(String name) { 
			_name = name; 
		}
		
		public static TaskFinishReason typeOf(String reason) {
			if (reason != null && reason.equalsIgnoreCase("success"))
				return TaskFinishReason.Success;
			return TaskFinishReason.Failure;
		}
		
		@Override
		public String toString() {
			
			if (this == null) 
				return "";
			
			return _name;
		}
	}
	
	private ChangeType _changeType;
	private String _taskName = "";
	private String _taskParameters = "";
	private String _planLabel = "";
	private String _taskId = "";
	private TaskFinishReason _taskFinishReason = TaskFinishReason.Success;
	private int _taskResultCode;
	private String _taskResultDescription = "";;
	
	public String getTaskParameters() {
		return _taskParameters;
	}
	
	public void setTaskParameters(String taskParameters) {
		if (taskParameters != null)
			this._taskParameters = taskParameters;
	}
	
	public String getTaskName() {
		return _taskName;
	}
	
	public void setTaskName(String taskName) {
		if (taskName != null)
			this._taskName = taskName;
	}

	public ChangeType getChangeType() {
		return _changeType;
	}

	public void setChangeType(ChangeType changeType) {
		this._changeType = changeType;
	}
	
	public void setChangeType(int typeCode) {
		this._changeType = ChangeType.typeOf(typeCode);
	}
	
	public String getPlanLabel() {
		return _planLabel;
	}

	public void setPlanLabel(String planLabel) {
		if (planLabel != null)
			this._planLabel = planLabel;
	}

	public String getTaskId() {
		return _taskId;
	}

	public void setTaskId(String taskId) {
		if (taskId != null)
			this._taskId = taskId;
	}

	public TaskFinishReason getTaskFinishReason() {
		return _taskFinishReason;
	}

	public void setTaskFinishReason(TaskFinishReason taskFinishReason) {
		this._taskFinishReason = taskFinishReason;
	}
	
	public void setTaskFinishReason(String taskFinishReason) {
		if (taskFinishReason != null)
			this._taskFinishReason = TaskFinishReason.typeOf(taskFinishReason);
	}
	
	public int getTaskResultCode() {
		return _taskResultCode;
	}

	public void setTaskResultCode(int taskResultCode) {
		this._taskResultCode = taskResultCode;
	}

	public String getTaskResultDescription() {
		return _taskResultDescription;
	}

	public void setTaskResultDescription(String taskResultDescription) {
		if (taskResultDescription != null)
			this._taskResultDescription = taskResultDescription;
	}
	
	public StackStreamMessage clone() {
		StackStreamMessage newMessage = new StackStreamMessage();
		newMessage.clone(this);
		return newMessage;
	}

	@Override
	public void clone(StackStreamMessage message) {
		setChangeType(message.getChangeType());
		setPlanLabel(message.getPlanLabel());
		setTaskFinishReason(message.getTaskFinishReason());
		setTaskId(message.getTaskId());
		setTaskName(message.getTaskName());
		setTaskParameters(message.getTaskParameters());
		setTaskResultCode(message.getTaskResultCode());
		setTaskResultDescription(message.getTaskResultDescription());
	}

	@Override
	public String toString() {
		return String.format(
				"Task Id: %s\nChange type: %d(%s)\nTask name: %s\nParameters: %s\nPlan execution label: %s\nResult code: %d\nResult description: %s\nFinish reason: %s",
				getTaskId(),
				getChangeType().getCode(), 
				getChangeType(), 
				getTaskName(), 
				getTaskParameters(),
				getPlanLabel(),
				getTaskResultCode(),
				getTaskResultDescription(),
				getTaskFinishReason());
	}
}
