#include <QDebug> // gilgil temp
#include <QGridLayout>

#include "gpropeditor.h"
#include "gpropitem_unknowntype.h"
#include "gpropitemfactory.h"

// ----------------------------------------------------------------------------
// GPropEditor
// ----------------------------------------------------------------------------
GPropEditor::GPropEditor(QWidget *parent) : QTreeWidget(parent)
{
  this->setColumnCount(2);
  QStringList sList; sList << "property" << "value";
  this->setHeaderLabels(sList);
  QLayout* layout = new QGridLayout(this);
  layout->setMargin(0);
  object_ = nullptr;
}

GPropEditor::~GPropEditor()
{
}

QObject* GPropEditor::object()
{
  return object_;
}

void GPropEditor::setObject(QObject* object)
{
  if (object == object_) return;
  object_ = object;
  GPropItemFactory& factory = GPropItemFactory::instance();

  const QMetaObject* mobj = object->metaObject();
  int propCount = mobj->propertyCount();
  for (int i = 0; i < propCount; i++)
  {
    QMetaProperty mpro = mobj->property(i);
    GPropItem* item = nullptr;
    GPropItemCreator* creatableObject = dynamic_cast<GPropItemCreator*>(object);
    GPropItemParam param {this, object, mpro};
    if (creatableObject != nullptr)
    {
      item = creatableObject->createItem(param);
    }
    if (item == nullptr)
    {
      item = factory.createItem(param);
    }
    if (item == nullptr)
    {
      qDebug() << "item is nullptr" << mpro.typeName() << mpro.name();
      new GPropItem_UnknownType(param);
    } else
    {
      item->update();
    }
  }
}
