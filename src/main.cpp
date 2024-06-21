#include <iostream>
#include <vector>
#include <sentencepiece_processor.h>
#include "ctranslate2/translator.h"
#include "ctranslate2/translation.h"

#include "fileManager/file_manager.hpp"
#include "translator/translator.hpp"
#include "tokenManager/token_manager.hpp"
#include "processCaller/process_caller_factory.hpp"

int main(/*int argc, char* argv[]*/) {

    ctranslate2::TranslationOptions tOptions;
    //tOptions.repetition_penalty = 1;
    //tOptions.length_penalty = 0.2;
    //tOptions.replace_unknowns = true;
    //tOptions.return_scores = true;
    //tOptions.beam_size = 4;

    mlcxc::FileManager fileManager;
    mlcxc::TokenManager tm;
    std::string res = mlcxc::StatusManager::
        getErrorMessage(fileManager.loadInput("../temp_src/main.cpp"));
    for (auto& it : fileManager.getSourceFiles())
    {
        tm.getFile(it.second);
    }

    std::vector<mlcxc::string_t> raw_words = tm.getWords();
    std::vector<std::vector<std::string>> payload(1);
    std::vector<mlcxc::string_t> mlcxcPayload;
    for(int i = 0 ; i < raw_words.size();i++)
    {
        payload[0].emplace_back(encoding_conv.to_bytes(raw_words[i]));
    }
    mlcxc::translator translator;
    translator.load_options(tOptions);
    std::vector<std::vector<std::string>> outvec = translator.translate_batch(payload);
    for(int i = 0 ; i < outvec[0].size();i++)
    {
        mlcxcPayload.emplace_back(encoding_conv.from_bytes(outvec[0][i]));
    }
    std::vector<mlcxc::string_t> subst_words = tm.getSubstitutedWords(mlcxcPayload);

   fileManager.saveFile("./outfile.cpp",subst_words);
    mlcxc::ProcessCaller *pc;
    mlcxc::process_caller_new(&pc);
    pc->call("g++ .\\outfile.cpp -o outprog");
    std::cout<<"\n";
    pc->call(".\\outprog");
    mlcxc::process_caller_destroy(&pc);
    return 0;
}