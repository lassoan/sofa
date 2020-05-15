/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include "DataTracker.h"
#include "objectmodel/BaseData.h"

namespace sofa
{

namespace core
{





void DataTracker::trackData( const objectmodel::BaseData& data )
{
    m_dataTrackers[&data] = data.getCounter();
}

bool DataTracker::hasChanged( const objectmodel::BaseData& data )
{
    return m_dataTrackers[&data] != data.getCounter();
}

bool DataTracker::hasChanged()
{
    for( DataTrackers::iterator it=m_dataTrackers.begin(),itend=m_dataTrackers.end() ; it!=itend ; ++it )
        if( it->second != it->first->getCounter() ) return true;
    return false;
}

void DataTracker::clean( const objectmodel::BaseData& data )
{
    m_dataTrackers[&data] = data.getCounter();
}

void DataTracker::clean()
{
    for( DataTrackers::iterator it=m_dataTrackers.begin(),itend=m_dataTrackers.end() ; it!=itend ; ++it )
        it->second = it->first->getCounter();
}



////////////////////
void DataTrackerDDGNode::addInputs(std::initializer_list<sofa::core::objectmodel::BaseData*> datas)
{
    for(sofa::core::objectmodel::BaseData* d : datas)
        addInput(d);
}

void DataTrackerDDGNode::addOutputs(std::initializer_list<sofa::core::objectmodel::BaseData*> datas)
{
    for(sofa::core::objectmodel::BaseData* d : datas)
        addOutput(d);
}

void DataTrackerDDGNode::cleanDirty(const core::ExecParams*)
{
    core::objectmodel::DDGNode::cleanDirty();

    /// it is also time to clean the tracked Data
    m_dataTracker.clean();
}

void DataTrackerDDGNode::updateAllInputsIfDirty()
{
    const DDGLinkContainer& inputs = DDGNode::getInputs();
    for(auto input : inputs)
    {
        static_cast<core::objectmodel::BaseData*>(input)->updateIfDirty();
    }
}
///////////////////////
void DataTrackerEngine::addCallback( std::function<void(DataTrackerEngine*)> f)
{
    m_callbacks.push_back(f);
}

void DataTrackerEngine::update()
{
    for(auto& callback : m_callbacks)
    {
        callback(this);
    }
}


}

}
