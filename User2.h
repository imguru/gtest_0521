class User {
	virtual ~User() {}  // 상속
	
	virtual void Stop() {}
	virtual void Move(int x, int y) {}

	virtual int GetX() const { return 0; }
	virtual int GetY() const { return 1; }
};
