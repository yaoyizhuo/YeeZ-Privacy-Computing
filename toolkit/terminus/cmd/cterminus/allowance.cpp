#include "cmd_line.h"
#include "ypc/terminus/enclave_interaction.h"

int generate_allowance(ypc::terminus::crypto_pack *crypto,
                       const boost::program_options::variables_map &vm) {
  ypc::bytes private_key = get_param_privatekey(vm);
  ypc::bytes param = ypc::bytes(vm["use-param"].as<std::string>());
  ypc::bytes enclave_hash =
      ypc::hex_bytes(vm["use-enclave-hash"].as<std::string>()).as<ypc::bytes>();
  ypc::bytes dian_pkey =
      ypc::hex_bytes(vm["tee-pubkey"].as<std::string>()).as<ypc::bytes>();
  ypc::bytes dhash =
      ypc::hex_bytes(vm["dhash"].as<std::string>()).as<ypc::bytes>();

  auto ei = ypc::terminus::enclave_interaction(crypto);
  // allowance is a ypc::bytes sig(65);
  ypc::bytes allowance = ei.generate_allowance(
      private_key, crypto->hash_256(param), enclave_hash, dian_pkey, dhash);

  ypc::bytes pkey = crypto->gen_ecc_public_key_from_private_key(private_key);

  std::unordered_map<std::string, ypc::bytes> result;
  result["signature"] = allowance;
  result["pkey"] = pkey;
  result["private_key"] = allowance;
  result["param"] = param;
  result["hash"] = crypto->hash_256(param);
  result["enclave_hash"] = enclave_hash;
  result["dian_pkey"] = dian_pkey;
  result["dhash"] = dhash;

  if (vm.count("output")) {
    std::string output_path =
        ypc::complete_path(vm["output"].as<std::string>());

    boost::property_tree::ptree pt;
    for (auto it = result.begin(); it != result.end(); it++) {
      pt.put(it->first, it->second);
    }
    boost::property_tree::json_parser::write_json(output_path, pt);
  } else {
    std::cout << "allowance_sig: " << allowance << std::endl;
    std::cout << "pkey: " << pkey << std::endl;
    std::cout << "private_key: " << private_key << std::endl;
    std::cout << "enclave_hash: " << enclave_hash << std::endl;
    std::cout << "dian_pkey: " << dian_pkey << std::endl;
    std::cout << "dhash: " << dhash << std::endl;
  }
  return 0;
}
