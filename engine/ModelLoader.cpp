#include "ModelLoader.h"

ModelLoader::ModelLoader(Shader& shader) : _shader(shader)
{
}

void ModelLoader::load()
{
  auto shellModel = std::make_unique<Model>(_shader);
  shellModel->load("/home/roman/repos/colony/assets/shell.dae");
  _models.emplace(Models::Shell, std::move(shellModel));

  auto tankModel = std::make_unique<Model>(_shader);
  tankModel->load("/home/roman/repos/colony/assets/tank.dae");
  tankModel->loadTexture("/home/roman/repos/colony/assets/blue.png",
                         TexturePackType::OnSelection);
  tankModel->loadTexture("/home/roman/repos/colony/assets/red.png",
                         TexturePackType::UnderFire);
  tankModel->loadTexture("/home/roman/repos/colony/assets/black.png",
                         TexturePackType::Destroyed);
  _models.emplace(Models::Tank, std::move(tankModel));

  auto tankFactoryModel = std::make_unique<Model>(_shader);
  tankFactoryModel->load("/home/roman/repos/colony/assets/garage.dae");
  tankFactoryModel->loadTexture("/home/roman/repos/colony/assets/grey.png",
                                TexturePackType::PreBuild);
  tankFactoryModel->loadTexture("/home/roman/repos/colony/assets/blue.png",
                                TexturePackType::OnSelection);
  tankFactoryModel->loadTexture("/home/roman/repos/colony/assets/red.png",
                                TexturePackType::UnderFire);
  tankFactoryModel->loadTexture("/home/roman/repos/colony/assets/black.png",
                                TexturePackType::Destroyed);
  _models.emplace(Models::TankFactory, std::move(tankFactoryModel));

  auto hqModel = std::make_unique<Model>(_shader);
  hqModel->load("/home/roman/repos/colony/assets/hq.dae");
  hqModel->loadTexture("/home/roman/repos/colony/assets/grey.png",
                       TexturePackType::PreBuild);
  hqModel->loadTexture("/home/roman/repos/colony/assets/blue.png",
                       TexturePackType::OnSelection);
  hqModel->loadTexture("/home/roman/repos/colony/assets/red.png",
                       TexturePackType::UnderFire);
  hqModel->loadTexture("/home/roman/repos/colony/assets/black.png",
                       TexturePackType::Destroyed);
  _models.emplace(Models::Hq, std::move(hqModel));

  auto plantModel = std::make_unique<Model>(_shader);
  plantModel->load("/home/roman/repos/colony/assets/plant.dae");
  _models.emplace(Models::Plant, std::move(plantModel));

  auto barrierModel = std::make_unique<Model>(_shader);
  barrierModel->load("/home/roman/repos/colony/assets/barrier.dae");
  barrierModel->loadTexture("/home/roman/repos/colony/assets/grey.png",
                            TexturePackType::PreBuild);
  barrierModel->loadTexture("/home/roman/repos/colony/assets/blue.png",
                            TexturePackType::OnSelection);
  barrierModel->loadTexture("/home/roman/repos/colony/assets/red.png",
                            TexturePackType::UnderFire);
  barrierModel->loadTexture("/home/roman/repos/colony/assets/black.png",
                            TexturePackType::Destroyed);
  _models.emplace(Models::Barrier, std::move(barrierModel));

  auto tfTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/Garage.png");
  tfTexture->load();
  _menuTextures.emplace(MenuTextures::TankFactory, std::move(tfTexture));

  auto hqTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/Hq.png");
  hqTexture->load();
  _menuTextures.emplace(MenuTextures::Hq, std::move(hqTexture));
  auto lightTankTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/lightTank.png");
  lightTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankLight, std::move(lightTankTexture));
  auto mediumTankTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/mediumTank.png");
  mediumTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankMedium, std::move(mediumTankTexture));
  auto heavyTankTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/heavyTank.png");
  heavyTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankHeavy, std::move(heavyTankTexture));

  auto plantTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/Plant.png");
  plantTexture->load();
  _menuTextures.emplace(MenuTextures::Plant, std::move(plantTexture));

  auto barrierTexture = std::make_shared<Texture>(
    GL_TEXTURE_2D, "/home/roman/repos/colony/assets/Barrier.png");
  barrierTexture->load();
  _menuTextures.emplace(MenuTextures::Barrier, std::move(barrierTexture));
}

ModelsMapping ModelLoader::models()
{
  return _models;
}

MenuTexturesMapping ModelLoader::menuTextures()
{
  return _menuTextures;
}
