#ifndef BUFFER_MANAGER_H_INCLUDED
#define BUFFER_MANAGER_H_INCLUDED

#include <cstdint>
#include <string>
#include <gtksourceviewmm.h>
#include <tr1/memory>

typedef uint32_t BufferID;
typedef Glib::RefPtr<Gsv::Buffer> BufferPtr;

class BufferManager {
public:
    typedef std::tr1::shared_ptr<BufferManager> ptr;

    BufferManager(Gsv::View& view);

    BufferID open_file(const std::string& filename);
    void save_buffer(BufferID buffer, const std::string& filename=std::string());
    void set_active_buffer(BufferID buffer);
    Glib::RefPtr<Gsv::Language> detect_language(const std::string& filename);
private:
    static BufferID counter_;

    Gsv::View& view_;
    std::map<BufferID, BufferPtr> buffers_;
    std::map<std::string, BufferPtr> buffers_by_filename_;

    BufferID get_buffer_id_from_filename(const std::string& filename);
    BufferPtr get_buffer_by_id(BufferID buffer_id);
};

#endif // BUFFER_MANAGER_H_INCLUDED
