#include "translator/translator.hpp"
#include "utils/string_util.hpp"

std::vector<std::vector<std::string>>
    mlcxc::translator::translate_batch(const std::vector<std::vector<std::string>>& source,
                    const ctranslate2::TranslationOptions& opt,
                    const size_t max_batch_size,
                    const ctranslate2::BatchType batch_type)
                    {
                        std::wstring debug_word;
                        std::vector<std::vector<std::string>> outvec(source.size());
                        const std::string model_path("E:\\Users_From_C\\LightError\\folder8\\MyProjects\\Cpp\\cpp-conosle-app\\Assets\\opus-mt-uk-en-ct2");
                        ctranslate2::models::ModelLoader model_loader(model_path);
                        ctranslate2::Translator translator(model_loader);
                        sentencepiece::util::Status status = enc.Load("E:\\Users_From_C\\LightError\\folder8\\MyProjects\\Cpp\\cpp-conosle-app\\Assets\\opus-mt-uk-en\\source.spm");
                        status = dec.Load("E:\\Users_From_C\\LightError\\folder8\\MyProjects\\Cpp\\cpp-conosle-app\\Assets\\opus-mt-uk-en\\target.spm");

                        for (int i = 0; i < source.size();i++)
                        {
                            std::vector<std::vector<std::string>> payload(source[i].size());
                            outvec[i].resize(source[i].size());
                            for (int j = 0; j < source[i].size();j++)
                            {
                                enc.Encode(source[i][j], &payload[j]);
                            }
                            std::vector<ctranslate2::TranslationResult> translation =translator.translate_batch(payload, options, max_batch_size);
                            for (int j = 0; j < source[i].size();j++)
                            {
                                dec.Decode(translation[j].output(),&outvec[i][j]);
                                int zxc = 0;
                            }
                        }                    
                        return outvec;
                    };

void mlcxc::translator::init(const ctranslate2::TranslationOptions& opt,const std::string &mpath)
{
    options = opt;
}

void mlcxc::translator::load_options(const ctranslate2::TranslationOptions& opt)
{
    options = opt;
}