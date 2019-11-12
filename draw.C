{
  gSystem->Load("libEve");
TEveManager::Create();
gGeoManager= gEve->GetGeometry("geom.root");
gGeoManager->DefaultColors();
gEve->FullRedraw3D(kTRUE);
mm=gGeoManager->GetTopVolume()->GetNode(0);
TEveGeoTopNode* ll= new TEveGeoTopNode(gGeoManager,mm);
gEve->AddGlobalElement(ll);
gEve->FullRedraw3D(kTRUE);
TGLViewer *v= gEve->GetDefaultGLViewer();
//v->GetClipSet()->SetClipType(1);
//v->SetCurrentCamera(TGLViewer::kCameraPerspXOY);
v->RefreshPadEditor(v);
v->DoDraw();
}
