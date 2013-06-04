#ifndef CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC

#include <map>

#include <glm/ext.hpp>

#include <cw/Enforce.hpp>

#include <cw/core/Logger.hpp>
#include <cw/graph/View.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/ShaderResourceLocator.hpp>
#include <cw/opengl/Plane.hpp>

namespace cw
{
  namespace opengl
  {
    /// helper functions

    /**
     *  Add 'normal' to 'vertexNormals'
     *  It push_back each coordinate of 'normal' (x,y,z)
     */
    template<typename Coord>
    void addNormal( std::vector<GLfloat> & vertexNormals, Coord normal );

    /**
     * Stores 'what' in buffer referenced by 'bufferId' with storage flag STATIC_DRAW
     */
    void storeDataInGPU( GLuint bufferId, const std::vector< GLfloat > & what );

    // TODO big and messy class, refactor somehow
    template<class ModelType>
    class OpenGlViewBase : public graph::View
    {
        // sets up the context (VAO,VBOs) for this object
        void show() override;
      protected:
        enum AttrIndex
        {
          POSITION = 0,
          COORD    = 1,
          NORMAL   = 2
        };
        typedef OpenGlViewBase<ModelType> BaseType;
        OpenGlViewBase( Ref<ModelType> model, ProjectionView & projView );

        void sendMVP( const glm::mat4 & model );
        void setModelVertices( std::initializer_list< GLfloat > vertices );
        void computeNormals();
        void sendColor( float r, float g, float b );
        auto getNumberOfVertices() -> std::vector<GLfloat>::size_type;


        Ref<ModelType> m_model;
        GLuint m_programId;
      private:
        // called from show()
        void virtual doShow() = 0;

        void setUpDraw();
        void initializeVBOs();

        GLuint m_vertexBufferId;
        GLuint m_normalBufferId;
        ProjectionView & m_projView;
        GLint m_colorUniformId;
        std::vector< GLfloat > m_vertexBuffer;
        ShaderResourceLocator m_shaderResourceLocator;
        GLuint m_vaoId;
    };

  }
}

#include "OpenGlViewBase.ipp"

#endif
