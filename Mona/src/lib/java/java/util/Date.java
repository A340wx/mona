package java.util;

/**
 ���t�Ǝ��Ԃ̃N���X
*/
public class Date {
	public int year, month, date, hour, minutes, second;
	
	private native void create(Date date);
	
	/** �f�t�H���g�R���X�g���N�^ */
	public Date() {
		create(this);
	}
	
	/** �N�𓾂� */
	public int getYear() {
		return this.year;
	}
	
	/** ���𓾂�(1-12) */
	public int getMonth() {
		return this.month;
	}
	
	/** ���𓾂�(1-31) */
	public int getDate() {
		return this.date;
	}
	
	/** ���𓾂�(1-24) */
	public int getHours() {
		return this.hour;
	}
	
	/** ���𓾂�(1-60) */
	public int getMinutes() {
		return this.minutes;
	}
	
	/** �b�𓾂�(1-60) */
	public int getSeconds() {
		return this.second;
	}
	
	/** �T�̗j���𓾂�(0-6) */
	public int getDay() {
		int y = this.year;
		int m = this.month;
		int d = this.date;
		
		// �c�F���[�̌���
		
		if ((m == 1) || (m == 2)) {
			y--;
			m += 12;
		}
		
		return ((y + (int)(y/4) - (int)(y/100) + (int)(y/400) + (int)((13 * m + 8)/5) + d) % 7);
	}
}
