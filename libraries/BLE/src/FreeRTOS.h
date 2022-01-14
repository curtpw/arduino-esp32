/*
 * FreeRTOS.h
 *
 *  Created on: Feb 24, 2017
 *      Author: kolban
 */

#ifndef MAIN_FREERTOS_H_
#define MAIN_FREERTOS_H_
#include <stdint.h>
#include <string>
#include <pthread.h>

#include <freertos/FreeRTOS.h>   // Include the base FreeRTOS definitions.
#include <freertos/task.h>       // Include the task definitions.
#include <freertos/semphr.h>     // Include the semaphore definitions.
#include <freertos/ringbuf.h>    // Include the ringbuffer definitions.

typedef enum {
	/**
	 * No-split buffers will only store an item in contiguous memory and will
	 * never split an item. Each item requires an 8 byte overhead for a header
	 * and will always internally occupy a 32-bit aligned size of space.
	 */
	RINGBUF_TYPE_NOSPLIT = 0,
	/**
	 * Allow-split buffers will split an item into two parts if necessary in
	 * order to store it. Each item requires an 8 byte overhead for a header,
	 * splitting incurs an extra header. Each item will always internally occupy
	 * a 32-bit aligned size of space.
	 */
	RINGBUF_TYPE_ALLOWSPLIT,
	/**
	 * Byte buffers store data as a sequence of bytes and do not maintain separate
	 * items, therefore byte buffers have no overhead. All data is stored as a
	 * sequence of byte and any number of bytes can be sent or retrieved each
	 * time.
	 */
	RINGBUF_TYPE_BYTEBUF
} ringbuf_type_t;


/**
 * @brief Interface to %FreeRTOS functions.
 */
class FreeRTOS {
public:
	static void sleep(uint32_t ms);
	static void startTask(void task(void*), std::string taskName, void* param = nullptr, uint32_t stackSize = 2048);
	static void deleteTask(TaskHandle_t pTask = nullptr);

	static uint32_t getTimeSinceStart();

	class Semaphore {
	public:
		Semaphore(std::string owner = "<Unknown>");
		~Semaphore();
		void        give();
		void        give(uint32_t value);
		void        giveFromISR();
		void        setName(std::string name);
		bool        take(std::string owner = "<Unknown>");
		bool        take(uint32_t timeoutMs, std::string owner = "<Unknown>");
		std::string toString();
		uint32_t	wait(std::string owner = "<Unknown>");
		bool		timedWait(std::string owner = "<Unknown>", uint32_t timeoutMs = portMAX_DELAY);
		uint32_t	value(){ return m_value; };

	private:
		SemaphoreHandle_t m_semaphore;
		pthread_mutex_t   m_pthread_mutex;
		std::string       m_name;
		std::string       m_owner;
		uint32_t          m_value;
		bool              m_usePthreads;

	};
};


/**
 * @brief Ringbuffer.
 */
class Ringbuffer {
public:
	Ringbuffer(size_t length, ringbuf_type_t type = RINGBUF_TYPE_NOSPLIT);
	~Ringbuffer();

	void*    receive(size_t* size, TickType_t wait = portMAX_DELAY);
	void     returnItem(void* item);
	bool     send(void* data, size_t length, TickType_t wait = portMAX_DELAY);
private:
	RingbufHandle_t m_handle;
};

#endif /* MAIN_FREERTOS_H_ */
