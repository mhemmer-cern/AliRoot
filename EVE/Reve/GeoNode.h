// $Header$

#ifndef REVE_ReveGeom_H
#define REVE_ReveGeom_H

#include <Reve/RenderElement.h>
#include <Reve/ZTrans.h>

class TGeoVolume;
class TGeoNode;
class TGeoHMatrix;
class TGeoManager;

class TGeoShape;
class TGeoShapeExtract;

namespace Reve {

class GeoNodeRnrEl : public RenderElement,
                     public TObject
{
  friend class GeoNodeRnrElEditor;

  GeoNodeRnrEl(const GeoNodeRnrEl&);            // Not implemented
  GeoNodeRnrEl& operator=(const GeoNodeRnrEl&); // Not implemented

protected:
  TGeoNode *fNode;

public:
  GeoNodeRnrEl(TGeoNode* node);

  virtual const Text_t* GetName()  const;
  virtual const Text_t* GetTitle() const;

  TGeoNode* GetNode() const { return fNode; }

  virtual Int_t ExpandIntoListTree(TGListTree* ltree, TGListTreeItem* parent);

  virtual void UpdateItems();

  virtual Bool_t CanEditRnrElement() { return false; }
  virtual void SetRnrSelf(Bool_t rnr);

  virtual Bool_t CanEditMainColor()  { return true; }
  virtual void SetMainColor(Color_t color);
  virtual void SetMainColor(Pixel_t pixel);

  void UpdateNode(TGeoNode* node);
  void UpdateVolume(TGeoVolume* volume);

  virtual void Draw(Option_t* option="");

  ClassDef(GeoNodeRnrEl, 1);
}; // endclass GeoNodeRnrEl

//----------------------------------------------------------------

class GeoTopNodeRnrEl : public GeoNodeRnrEl
{
  GeoTopNodeRnrEl(const GeoTopNodeRnrEl&);            // Not implemented
  GeoTopNodeRnrEl& operator=(const GeoTopNodeRnrEl&); // Not implemented

protected:
  TGeoManager* fManager;
  TGeoHMatrix* fGlobalTrans;
  Bool_t       fUseNodeTrans;
  Int_t        fVisOption;
  Int_t        fVisLevel;  

public:
  GeoTopNodeRnrEl(TGeoManager* manager, TGeoNode* node, Int_t visopt=1, Int_t vislvl=3);
  virtual ~GeoTopNodeRnrEl();

  TGeoHMatrix *GetGlobalTrans()  const { return fGlobalTrans; }
  void         SetGlobalTrans(TGeoHMatrix* m);
  Bool_t       GetUseNodeTrans() const { return fUseNodeTrans; }
  void         SetUseNodeTrans(Bool_t u=kTRUE);

  Int_t GetVisOption() const { return fVisOption; }
  void  SetVisOption(Int_t visopt);
  Int_t GetVisLevel()  const { return fVisLevel; }
  void  SetVisLevel(Int_t vislvl);

  virtual void UpdateItems();

  virtual Bool_t CanEditRnrElement() { return true; }
  virtual void SetRnrSelf(Bool_t rnr);

  virtual void Draw(Option_t* option="");
  virtual void Paint(Option_t* option="");

  // Signals from GeoManager.
  // These are not available any more ... colors in list-tree not refreshed
  // properly.
  void VolumeVisChanged(TGeoVolume* volume);
  void VolumeColChanged(TGeoVolume* volume);
  void NodeVisChanged(TGeoNode* node);

  ClassDef(GeoTopNodeRnrEl, 1);
}; // endclass GeoTopNodeRnrEl


//----------------------------------------------------------------
//----------------------------------------------------------------

class GeoShapeRnrEl : public RenderElement,
		      public TNamed
{
  GeoShapeRnrEl(const GeoShapeRnrEl&);            // Not implemented
  GeoShapeRnrEl& operator=(const GeoShapeRnrEl&); // Not implemented

protected:
  ZTrans            fHMTrans;
  Color_t           fColor;
  UChar_t           fTransparency;
  TGeoShape*        fShape;

  static Int_t SubImportShapeExtract(TGeoShapeExtract* gse, RenderElement* parent);

public:
  GeoShapeRnrEl(const Text_t* name="GeoShapeRnrEl", const Text_t* title=0);
  virtual ~GeoShapeRnrEl();

  virtual Bool_t CanEditMainColor() { return kTRUE; }

  ZTrans& RefHMTrans() { return fHMTrans; }
  void SetTransMatrix(Double_t* carr)        { fHMTrans.SetFrom(carr); }
  void SetTransMatrix(const TGeoMatrix& mat) { fHMTrans.SetFrom(mat);  }

  Color_t     GetColor()        { return fColor; }
  UChar_t     GetTransparency() { return fTransparency; }
  TGeoShape*  GetShape()        { return fShape; }

  virtual void Paint(Option_t* option="");

  static Int_t ImportShapeExtract(TGeoShapeExtract* gse, RenderElement* parent);

  ClassDef(GeoShapeRnrEl, 1);
};

}

#endif
