#ifndef DATAMETADATA_H_
#define DATAMETADATA_H_

#include <string>
#include <vector>
#include <map>

namespace fl {
    class DataMetadata {
        private:
            std::map<std::string, std::string> metadata;
        public:
            std::string get(const std::string&) const;
            std::string toJsonString() const;
            static DataMetadata fromJsonString(const std::string&);

        protected:
            DataMetadata();
            void set(const std::string&, const std::string&);

        protected:
            static const std::string SAVE_RESULT_KEY;
            static const std::string SAVE_RESULT_VALUE_SUCCESS;
            static const std::string SAVE_RESULT_VALUE_FAILED;
            static const std::string DATA_FILE_KEY;
            static const std::string INDEX_FILE_KEY;
            static const int INDEX_LENGTH;

        friend class DataDeserializer;
        friend class DataSerializer;
    };
}

#endif

