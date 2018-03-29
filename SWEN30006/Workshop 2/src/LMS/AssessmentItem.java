package LMS;

import java.util.ArrayList;

public class AssessmentItem {
	private String title;
	private String dueDate;
	private ArrayList<Submission> submissions;
	private Subject subject;
	
	public AssessmentItem() {
		
	}
	
	public boolean makeSubmission(Submission s) {
		return true;
	}
}