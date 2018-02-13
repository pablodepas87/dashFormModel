#include "formmodel.h"

#include <QColor>
#include <QDebug>


FormModel::FormModel(QObject *parent):QAbstractListModel(parent)
{
    for(int i=0; i<10; i++){
        Form form;
        form.nameForm = QString("name %1").arg(i);
        for(int j=0; j<9; j++){
            QColor color(qrand() % 256, qrand() % 256, qrand() % 256);
            Tile tile{QString("name %1 %2").arg(i).arg(j), color.name()};
            form.grid<< QVariant::fromValue(tile);
        }
        dashboard<< form;
    }
    changeColor(0,1,QColor ("#ffffff"));
}


QHash<int, QByteArray> FormModel::roleNames() const
{
    QHash <int,QByteArray> roles;
    roles [NameForm]="nameForm";
    roles [Grid]="grid";
    return roles;
}

int FormModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dashboard.count();
}

QVariant FormModel::data(const QModelIndex &index, int role) const
{
    if(index.row()<0 && index.row() >= dashboard.count())
        return QVariant();
    Form dashTemp = dashboard[index.row()];
    if(role== NameForm)
        return dashTemp.nameForm;
    else if(role== Grid)
        return dashTemp.grid;
    return QVariant();
}

bool FormModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid())
        {
        return false;
        }

    switch (role) {
      case NameForm:
        dashboard[index.row()].nameForm=  value.toString();
        emit dataChanged(index,index);
        break;
      case Grid:
            dashboard[index.row()].grid.clear();
            dashboard[index.row()].grid <<QVariant::fromValue(value);
            emit dataChanged(index,index);
            break;
      default:
            break;
    }

    return true;

}

void FormModel::changeColor(int numGrid, int indexTile, QColor colore)
{

   Form temp= dashboard[numGrid];
   temp.nameForm="pippi";
   dashboard[numGrid]=temp;

   /*
    per modificare un elemento della griglia che è un QVariantList devo usare .value
    il canConvert è solo una verifica
   */
   qDebug()<< temp.grid[0].canConvert<Tile>();
   Tile tempT =  temp.grid[0].value<Tile>();

   qDebug()<< QVariant::fromValue(temp.nameForm)<<tempT.name ;
   beginResetModel();

}
