#ifndef TRANSLATOR_HPP_
#define TRANSLATOR_HPP_

#include <sentencepiece_processor.h>
#include "ctranslate2/translator.h"
#include "ctranslate2/translation.h"

namespace mlcxc
{
class translator
{
    public:
ctranslate2::TranslationOptions options;
//ctranslate2::Translator ct2_translator;
//ctranslate2::models::ModelLoader model_loader;
sentencepiece::SentencePieceProcessor enc;
sentencepiece::SentencePieceProcessor dec;

    std::vector<std::vector<std::string>>
    translate_batch(const std::vector<std::vector<std::string>>& source,
                    const ctranslate2::TranslationOptions& opt = ctranslate2::TranslationOptions(),
                    const size_t max_batch_size = 0,
                    const ctranslate2::BatchType batch_type = ctranslate2::BatchType::Examples);
    void load_options(const ctranslate2::TranslationOptions& opt);
    void init(const ctranslate2::TranslationOptions& opt,const std::string &mpath);
};
}
#endif TRANSLATOR_HPP_