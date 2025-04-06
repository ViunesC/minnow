#include "byte_stream.hh"
#include <queue>

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), stream() {}

void Writer::push( string data )
{
  int push_size = min(available_capacity(), data.length());

  for (int i=0;i<push_size;++i) {
    stream.push(data[i]);
    bytes_in_stream_++;
    push_total_++;
  }
}

void Writer::close()
{
  close_ = true;
}

bool Writer::is_closed() const
{
  return { close_ }; // Your code here.
}

uint64_t Writer::available_capacity() const
{
  return { capacity_ - bytes_in_stream_}; // Your code here.
}

uint64_t Writer::bytes_pushed() const
{
  return { push_total_ }; // Your code here.
}

string_view Reader::peek() const
{
  return { std::string_view(&stream.front(), 1) }; // Your code here.
}

void Reader::pop( uint64_t len )
{
  for (uint64_t i=len;i>0;--i) {
    if (bytes_in_stream_ == 0) {
      break;
    }

    stream.pop();
    pop_total_++;

    bytes_in_stream_--;
  }
}

bool Reader::is_finished() const
{
  return { stream.empty() && close_ }; // Your code here.
}

uint64_t Reader::bytes_buffered() const
{
  return { bytes_in_stream_ }; // Your code here.
}

uint64_t Reader::bytes_popped() const
{
  return { pop_total_ }; // Your code here.
}

