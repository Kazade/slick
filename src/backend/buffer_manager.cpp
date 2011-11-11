#include <cassert>

#include "buffer_manager.h"
#include "kazbase/file_utils.h"
#include "kazbase/list_utils.h"

BufferID BufferManager::counter_ = 0;

BufferManager::BufferManager(Gsv::View& view):
    view_(view) {

}

/**
    Opens a file by its filename. If a buffer already exists for the filename
    then return the id, otherwise, create a new buffer
    with the file contents and then return that id
*/
BufferID BufferManager::open_file(const std::string& filename) {
    if(container::contains(buffers_by_filename_, filename)) {
        BufferID buffer_id = get_buffer_id_from_filename(filename);
        return buffer_id;
    }

    BufferID new_buffer_id = counter_++;
    BufferPtr new_buffer = Gsv::Buffer::create();
    new_buffer->set_text(file_utils::read_contents(filename));
    buffers_[new_buffer_id] = new_buffer;

    return new_buffer_id;
}

void BufferManager::save_buffer(BufferID buffer, const std::string& filename) {
    /*
        TODO:
        1. Copy existing file
        2. Create new file with the content of the buffer
        3. Delete copy
        4. Mark as unaltered
    */
}

void BufferManager::set_active_buffer(BufferID buffer_id) {
    BufferPtr buffer = get_buffer_by_id(buffer_id);
    view_.set_source_buffer(buffer);
}

BufferID BufferManager::get_buffer_id_from_filename(const std::string& filename) {
    assert(container::contains(buffers_by_filename_, filename));
    return buffers_by_filename_[filename];
}

BufferPtr BufferManager::get_buffer_by_id(BufferID buffer_id) {
    assert(container::contains(buffers_, buffer_id));
    return buffers_[buffer_id];
}
