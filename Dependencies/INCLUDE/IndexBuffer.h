#pragma once

class IndexBuffer {
private:
	unsigned int m_renderer_id;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void bindIndex() const;
	void unBindIndex() const;
	void deleteIndex() const;
	inline unsigned int getCount() const { return m_count; }
};